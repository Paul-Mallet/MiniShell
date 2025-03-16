/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:36:08 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/16 19:10:10 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

int	exec_command(t_cmd *cmds, t_data *data, t_cmd_order nbr, int *i)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		path = check_path(data, cmds->cmd[0]);
		if (!path)
		{
			close_pipes(cmds);
			free_data(data);
			exit (2);
		}
		executing_command(cmds, path, data, nbr);
	}
	data->pids[*i] = pid;
	*i += 1;
	return (EXIT_SUCCESS);
}

int	exec_simple_cmd(t_data *data)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		path = check_path(data, data->cmds->cmd[0]);
		if (!path)
		{
			free_data(data);
			exit (2);
		}
		executing_simple_cmd(data, path);
	}
	else
	{
		waitpid(pid, &data->exit_code, 0);
		if (WIFEXITED(data->exit_code))
			data->exit_code = WEXITSTATUS(data->exit_code);
	}
	return (EXIT_SUCCESS);
}

// int	error_path(char **paths, char *path, t_data *data)
// {
// 	error_handling(ERR_CMD_NOT_FOUND, path);
// 	free_paths(paths, NULL);
// 	data->exit_code = 127;
// 	return (EXIT_FAILURE);
// }
