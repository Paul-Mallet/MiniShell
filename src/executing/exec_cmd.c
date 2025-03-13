/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:36:08 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/13 17:25:36 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

int	exec_command(t_cmd *cmds, t_data *data, int *i)
{
	pid_t	pid;
	char	**paths;
	char	*path;

	paths = get_path_vrbl(data->env);
	path = find_path(paths, cmds->cmd[0]);
	if (!path)
		return (error_path(paths, data->prompt, data));
	if (pipe(cmds->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
		executing_command(cmds, path, data);
	free_paths(paths, path);
	data->pids[*i] = pid;
	*i += 1;
	return (EXIT_SUCCESS);
}

int	exec_first_cmd(t_cmd *cmds, t_data *data, int *i)
{
	pid_t	pid;
	char	**paths;
	char	*path;

	paths = get_path_vrbl(data->env);
	path = find_path(paths, cmds->cmd[0]);
	if (!path)
		return (error_path(paths, data->prompt, data));
	if (pipe(cmds->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
		executing_first_cmd(cmds, path, data);
	else
		close(cmds->fd[1]);
	free_paths(paths, path);
	data->pids[*i] = pid;
	*i += 1;
	return (EXIT_SUCCESS);
}

int	exec_last_cmd(t_cmd *cmds, t_data *data, int *i)
{
	pid_t	pid;
	char	**paths;
	char	*path;

	paths = get_path_vrbl(data->env);
	path = find_path(paths, cmds->cmd[0]);
	if (!path)
		return (error_path(paths, data->prompt, data));
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
		executing_last_cmd(cmds, path, data);
	else
	{
		close(cmds->prev->fd[0]);
		close_all_pipes(cmds);
	}
	free_paths(paths, path);
	data->pids[*i] = pid;
	*i += 1;
	return (EXIT_SUCCESS);
}

int	exec_simple_cmd(t_data *data)
{
	pid_t	pid;
	char	**paths;
	char	*path;

	paths = get_path_vrbl(data->env);
	path = find_path(paths, data->cmds->cmd[0]);
	if (!path)
		return (error_path(paths, data->prompt, data));
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
		executing_simple_cmd(data, path);
	else
	{
		waitpid(pid, &data->exit_code, 0);
		if (WIFEXITED(data->exit_code))
			data->exit_code = WEXITSTATUS(data->exit_code);
	}
	free_paths(paths, path);
	return (EXIT_SUCCESS);
}

int	error_path(char **paths, char *path, t_data *data)
{
	error_handling(ERR_CMD_NOT_FOUND, path);
	free_paths(paths, NULL);
	data->exit_code = 127;
	return (EXIT_FAILURE);
}
