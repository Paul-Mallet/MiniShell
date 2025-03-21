/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:36:08 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/21 19:22:52 by abarahho         ###   ########.fr       */
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
		if (!cmds->cmd[0] || data->exit_code == 1)
		{
			free_pids(data);
			exit(1);
		}
		path = check_path(data, cmds->cmd[0]);
		if (!path)
		{
			free_pids(data);
			exit(data->exit_code);
		}
		executing_command(cmds, path, data, nbr);
	}
	data->pids[*i] = pid;
	*i += 1;
}

void	wait_simple_cmd(t_data *data, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_code = 128 + WTERMSIG(status);
}

void	exec_simple_cmd(t_data *data)
{
	pid_t	pid;

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
			if (!data->cmds->cmd[0] || data->exit_code == 1)
			{
				free_data(data);
				exit(1);
			}
			executing_simple_cmd(data);
		}
		else
			wait_simple_cmd(data, pid);
	}
}
