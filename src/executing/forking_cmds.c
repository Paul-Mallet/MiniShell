/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:36:08 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 14:40:09 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

void	exec_command(t_cmd *cmds, t_data *data, t_cmd_order nbr, int *i)
{
	pid_t	pid;
	char	*path;

	path = NULL;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		check_redir(cmds);
		if (!cmds->cmd)
		{
			close_pipes(cmds);
			free_data(data);
			exit (1);			
		}
		if (is_builtins(cmds->cmd[0]))
			ft_builtins(data, cmds);
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
}

void	exec_simple_cmd(t_data *data)
{
	pid_t	pid;

	check_redir(data->cmds);
	if (!data->cmds->cmd)
		return ;			
	if (is_builtins(data->cmds->cmd[0]))
		ft_builtins(data, data->cmds);
	else 
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
			executing_simple_cmd(data);
		else
		{
			waitpid(pid, &data->exit_code, 0);
			if (WIFEXITED(data->exit_code))
				data->exit_code = WEXITSTATUS(data->exit_code);
		}
	}
}

// int	error_path(char **paths, char *path, t_data *data)
// {
// 	error_handling(ERR_CMD_NOT_FOUND, path);
// 	free_paths(paths, NULL);
// 	data->exit_code = 127;
// 	return (EXIT_FAILURE);
// }
