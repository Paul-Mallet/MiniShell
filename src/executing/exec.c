/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:26:39 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/16 18:56:01 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

// static void checkid(t_cmd *cmds)
// {
// 	t_cmd	*current;
// 	int	i;

// 	current = cmds;
// 	i = 0;
// 	while (current)
// 	{
// 		printf("checkid ;%d\n", current->id);
// 		current = current->next;
// 	}
// }

void	init_id_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	int	i;

	current = cmds;
	i = 0;
	while (current)
	{
		current->id = i;
		i++;
		current = current->next;
	}
}

void	exec(t_data *data)
{
	t_cmd	*current;
	int		nb_cmd;
	int		i;

	i = 0;
	check_heredoc(data);
	nb_cmd = count_cmds(data->cmds);
	current = data->cmds;
	if (!data->cmds)
		return ;
	data->char_env = make_env(data->env);
	// printf("\nnb cmd ;%d\n", nb_cmd);
	if (nb_cmd == 1)
	{
		exec_simple_cmd(data);
		return ;
	}
	init_id_cmds(data->cmds);
	data->pids = malloc(sizeof(int) * nb_cmd);
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
		if (current->prev)
			close_pipes(current->prev);
		current = current->next;
	}
	close_all_pipes(data->cmds);
	wait_all(data);
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
		}
		i++;
		current = current->next;
	}
}
