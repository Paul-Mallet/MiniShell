/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:33:03 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/25 12:18:57 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"
#include "signals.h"

void	init_id_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	int		i;

	current = cmds;
	i = 0;
	while (current)
	{
		current->id = i;
		i++;
		current = current->next;
	}
}

void	wait_all(t_data *data)
{
	int		status;
	int		pid;
	int		i;
	t_cmd	*current;

	i = 0;
	current = data->cmds;
	while (current)
	{
		pid = waitpid(data->pids[i], &status, 0);
		if (pid > 0)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = 128 + WTERMSIG(status);
		}
		i++;
		current = current->next;
	}
}

void	exec_multiple_cmds(t_data *data, int nb_cmd)
{
	t_cmd	*current;
	int		i;

	current = data->cmds;
	i = 0;
	data->pids = (int *)malloc(sizeof(int) * nb_cmd);
	while (current)
	{
		if (current->next && pipe(current->fd) == -1)
		{
			perror("pipe");
			return ;
		}
		if (current->id == 0)
			exec_command(current, data, FIRST_CMD, &i);
		else if (current->id == (nb_cmd - 1))
			exec_command(current, data, LAST_CMD, &i);
		else
			exec_command(current, data, MID_CMD, &i);
		current = current->next;
	}
	close_all_pipes(data->cmds);
	wait_all(data);
	free(data->pids);
}
