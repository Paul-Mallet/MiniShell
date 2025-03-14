/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:26:39 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/14 17:36:38 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

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


int	exec(t_data *data)
{
	t_cmd	*current;
	int		nb_cmd;


	check_heredoc(data);
	current = data->cmds;
	if (!data->cmds)
		return (EXIT_FAILURE);
	data->char_env = make_env(data->env);
	if (!data->char_env)
		return (EXIT_FAILURE);
	if ((count_cmds(data->cmds) == 1))
	{
		if (is_builtins(current->cmd[0]))
			return (ft_builtins(data, data->cmds));
		else
			return (exec_simple_cmd(data));
	}
	else
	{
		nb_cmd = count_cmds(data->cmds);
		init_id_cmds(data->cmds);
		data->pids = malloc(sizeof(int) * nb_cmd);
		return (exec_multiple_cmds(data));
	}
	return (1);
}

int	exec_multiple_cmds(t_data *data)
{
	t_cmd	*current;
	int		i;

	i = 0;
	current = data->cmds;
	// printf("count: %d \n", count_cmds(data->cmds));
	while (current)
	{
		if (!current->prev)
		{
			// printf("test_frst\n");
			exec_first_cmd(current, data, &i);
				// return (EXIT_FAILURE);
		}
		else if (current->prev && current->next)
		{
			// printf("test_between\n");
			exec_command(current, data, &i);
				// return (EXIT_FAILURE);
		}
		else if (!current->next)
		{
			// printf("test_las\n");
			exec_last_cmd(current, data, &i);
				// return (EXIT_FAILURE);
		}
		// if (current->prev)
		// 	close(current->prev->fd[0]);
		// if (current->next)
		// 	close(current->fd[1]);
		current = current->next;
	}
	// printf("test_wait\n");
	wait_all(data);
	return (EXIT_SUCCESS);
}

void	wait_all(t_data *data)
{
	int		status;
	int		pid;
	t_cmd	*current;
	int		i;

	i = 0;
	current = data->cmds;
	printf("before waiting\n");
	while (current)
	{
		printf("while waiting\n");
		printf("pid[%d]\n", data->pids[i]);
		pid = waitpid(data->pids[i], &status, 0);
		printf("pid: %d\n", pid);
		if (pid > 0)
		{
			printf("pid waiting\n");
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			printf("waiting\n");
		}
		// printf("before closing pipes waiting\n");
		// close_all_pipes(current);
		// printf("after closing pipes waiting\n");
		i++;
		current = current->next;
	}
	printf("after while\n");
}
