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

int	exec_simple_cmd(t_data *data, char **char_env)
{
	pid_t	pid;
	char	**paths;
	char	*path;

	paths = get_path_vrbl(data->env);
	if (!paths)
	{
		return (0);
	}
	path = find_path(paths, data->cmds->cmd[0]);
	if (!path)
	{
		return (0);
	}
	printf("%s\n", path);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// signal(SIGINT, SIG_DFL); //ctrl + C (^C + new line)
		// signal(SIGQUIT, SIG_DFL); //ctrl + \ (core dump)
		redir_managing(data);
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

void	exec(t_data *data)
{
	int		nb_cmd;
	char	**char_env;

	if (!data->cmds)
		return ;
	check_heredoc(data);
	char_env = make_env(data->env);
	if (!char_env)
		return ;
	exec_simple_cmd(data, char_env);
	(void)nb_cmd;
}


// int	exec_command(t_data *data, char **envp)
// {
// 	pid_t	pid;
// 	char	*path;

// 	path = find_path(envp, data->cmds->cmd[0]);
// 	if (!path)
// 	{
// 		perror("find_path");
// 		return (EXIT_FAILURE);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		free(path);
// 		return (EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
// 		// signal(SIGINT, SIG_DFL); //ctrl + C (^C + new line)
// 		// signal(SIGQUIT, SIG_DFL); //ctrl + \ (core dump)
// 		redir_managing(data);
// 		execve(path, data->cmds->cmd, envp);
// 		perror("execve");
// 		free(path);
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 		waitpid(pid, &data->exit_code, 0);
// 	free(path);
// 	return (1);
// }




