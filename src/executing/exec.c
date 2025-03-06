// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/13 17:26:39 by abarahho          #+#    #+#             */
// /*   Updated: 2025/02/27 17:02:54 by abarahho         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"


void	exec(t_data *data)
{
	int		nb_cmd;
	char	**char_env;
	t_cmd	*current;

	if (!data->cmds)
		return ;
	char_env = make_env(data->env);
	if (!char_env)
		return ;
	nb_cmd = count_cmds(data->cmds);
	printf("%d\n", nb_cmd);
	check_heredoc(data);
	current = data->cmds;
	if (!data->cmds->next)
		exec_simple_cmd(data, char_env);
	else
	{
		while (current)
		{
			if (!current->prev)
				exec_first_cmd(current, char_env, data->env);
			else if (!current->next)
				exec_last_cmd(current, char_env, data->env);
			else
				exec_command(current, char_env, data->env);
			current = current->next;
		}
		wait_all(data, nb_cmd);
	}
	free_strs(char_env);
}

int	exec_command(t_cmd *cmds, char **char_env, t_env *env)
{
	pid_t	pid;
	char	**paths;
	char	*path;

	paths = get_path_vrbl(env);
	if (!paths)
		return (0);
	path = find_path(paths, cmds->cmd[0]);
	if (!path)
		return (0);
	if (pipe(cmds->fd))
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); //ctrl + C (^C + new line)
		signal(SIGQUIT, SIG_DFL); //ctrl + \ (core dump)
		redir_managing(cmds);
		dup2(cmds->prev->fd[0], STDIN_FILENO);
		dup2(cmds->fd[1], STDOUT_FILENO);
		close(cmds->prev->fd[0]);
		close(cmds->fd[1]);
		execve(path, cmds->cmd, char_env);
		perror("execve");
		free(path);
		exit(EXIT_FAILURE);
	}
	free(path);
	return (1);
}

int	exec_first_cmd(t_cmd *cmds, char **char_env, t_env *env)
{
	pid_t	pid;
	char	**paths;
	char	*path;

	paths = get_path_vrbl(env);
	if (!paths)
		return (0);
	path = find_path(paths, cmds->cmd[0]);
	if (!path)
		return (0);
	if (pipe(cmds->fd))
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); //ctrl + C (^C + new line)
		signal(SIGQUIT, SIG_DFL); //ctrl + \ (core dump)
		dup2(cmds->fd[1], STDOUT_FILENO);
		close(cmds->fd[0]);
		close(cmds->fd[1]);
		redir_managing(cmds);
		execve(path, cmds->cmd, char_env);
		perror("execve");
		free(path);
		exit(EXIT_FAILURE);
	}
	else
		close(cmds->fd[1]);
	free(path);
	return (1);
}

int exec_last_cmd(t_cmd *cmds, char **char_env, t_env *env)
{
    pid_t pid;
    char **paths;
    char *path;

    paths = get_path_vrbl(env);
    if (!paths)
        return (0);
    path = find_path(paths, cmds->cmd[0]);
    if (!path)
        return (0);

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(path);
        return (EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        signal(SIGINT, SIG_DFL); // ctrl + C (^C + new line)
        signal(SIGQUIT, SIG_DFL); // ctrl + \ (core dump)
        if (cmds->prev)
        {
            dup2(cmds->prev->fd[0], STDIN_FILENO);
            close(cmds->prev->fd[0]);
        }
        redir_managing(cmds);
        execve(path, cmds->cmd, char_env);
        perror("execve");
        free(path);
        exit(EXIT_FAILURE);
    }
    else
    {
        if (cmds->prev)
            close(cmds->prev->fd[0]);
        if (cmds->fd[0] >= 0)
            close(cmds->fd[0]);
        if (cmds->fd[1] >= 0)
            close(cmds->fd[1]);
    }

    free(path);
    return (1);
}

int	exec_simple_cmd(t_data *data, char **char_env)
{
	pid_t	pid;
	char	**paths;
	char	*path;

	paths = get_path_vrbl(data->env);
	if (!paths)
		return (0);
	path = find_path(paths, data->cmds->cmd[0]);
	if (!path)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); //ctrl + C (^C + new line)
		signal(SIGQUIT, SIG_DFL); //ctrl + \ (core dump)
		redir_managing(data->cmds);
		execve(path, data->cmds->cmd, char_env);
		perror("execve");
		free(path);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &data->exit_code, 0);
		if (WIFEXITED(data->exit_code))
    		data->exit_code = WEXITSTATUS(data->exit_code);
	}
	free(path);
	return (1);
}

void	wait_all(t_data *data, int nb_cmd)
{
	int		status;
	int		pid;
	t_cmd	*current;

	current = data->cmds;
	while (nb_cmd--)
	{
		pid = waitpid(0, &status, 0);
		if (pid > 0)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
		}
		if (current->fd[0] >= 0)
			close(current->fd[0]);
		if (current->fd[1] >= 0)
			close(current->fd[1]);
		current = current->next;
	}
}
