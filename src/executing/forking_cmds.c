/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:36:08 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 08:40:12 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"
#include "signals.h"

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
		check_redir(cmds, data);
		if (!cmds->cmd)
		{
			close_pipes(cmds);
			free_data(data);
			exit(1);
		}
		if (is_builtins(cmds->cmd[0]))
			ft_builtins(data, cmds);
		path = check_path(data, cmds->cmd[0]);
		if (!path)
		{
			// free_strs(data->char_env);
			close_pipes(cmds);
			free_data(data);
			exit(2);
		}
		executing_command(cmds, path, data, nbr);
	}
	data->pids[*i] = pid;
	*i += 1;
}

void	exec_simple_cmd(t_data *data)
{
	pid_t	pid;
	int		status;
	
	if (is_builtins(data->cmds->cmd[0]) && !data->cmds->redir)
		ft_builtins(data, data->cmds);
	else 
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			check_redir(data->cmds, data);
			executing_simple_cmd(data);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = 128 + WTERMSIG(status);
		}
	}
	// if (data->exit_code != 0)
	// 	return (false);
	// return (true);
}

// int	error_path(char **paths, char *path, t_data *data)
// {
// 	error_handling(ERR_CMD_NOT_FOUND, path);
// 	free_paths(paths, NULL);
// 	data->exit_code = 127;
// 	return (EXIT_FAILURE);
// }
