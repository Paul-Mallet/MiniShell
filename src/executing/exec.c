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

void	exec(t_data *data)
{
	int		nb_cmd;
	int		i;
	char	**envp;
	int		prev_pipe;
	bool	is_last_cmd;

	envp = make_env(data->env);
	i = 0;
	check_heredoc(data);
	printf("\nexec\n");
	ft_builtins(data);
	nb_cmd = count_cmds(data->cmds);
	prev_pipe = -1;
	while (i < nb_cmd)
	{
		is_last_cmd = (i == nb_cmd - 1);
		setup_pipes(data->cmds, &prev_pipe, is_last_cmd);
		exec_command(data, envp, &prev_pipe, is_last_cmd);
		data->cmds = data->cmds->next;
		i++;
	}
	free_strs(envp);
}



int	exec_command(t_data *data, char **envp, int *prev_pipe, bool is_last_cmd)
{
	pid_t	pid;
	char	*path;

	path = find_path(envp, data->cmds->cmd[0]);
	if (!path)
	{
		perror("find_path");
		return (EXIT_FAILURE);
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
		setup_pipes(data->cmds, prev_pipe, is_last_cmd);
		redir_managing(data);
		execve(path, data->cmds->cmd, envp);
		perror("execve");
		free(path);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (*prev_pipe != -1)
			close(*prev_pipe);
		if (!is_last_cmd)
		{
			close(data->cmds->fd[1]);
			*prev_pipe = data->cmds->fd[0];
		}
		waitpid(pid, &data->exit_code, 0);
	}
	free(path);
	return (1);
}

char	**make_env(t_env *env)
{
	t_env	*current;
	char	**envp;
	int		i;

	current = env;
	i = 0;
	while(current)
	{
		i++;
		current = current->next;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		envp[i] = join_lines(current->key, "=");
		envp[i] = join_lines(envp[i], current->value);
		i++;
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	setup_pipes(t_cmd *cmd, int *prev_pipe, bool is_last_cmd)
{
	// Crée un nouveau pipe si ce n'est pas la dernière commande
	if (!is_last_cmd && pipe(cmd->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	// Redirige l'entrée depuis le pipe précédent (si existant)
	if (*prev_pipe != -1)
	{
		dup2(*prev_pipe, STDIN_FILENO);
		close(*prev_pipe);
	} 
	// Redirige la sortie vers le pipe suivant (si existant)
	if (!is_last_cmd)
	{
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
}