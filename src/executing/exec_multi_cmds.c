/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:33:03 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 14:42:41 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"
#include "signals.h"

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


// void	wait_all(t_data *data)
// {
// 	(void)data;
// 	int		status;
// 	pid_t	pid;

// 	while (1)
// 	{
// 		pid = waitpid(-1, &status, 0);
// 		if (pid == -1)
// 			break ;
// 	}
// }

void	exec_multiple_cmds(t_data *data, int nb_cmd)
{
	t_cmd	*current;
	int		i;

	current = data->cmds;
	i = 0;
	data->pids = (int *)malloc(sizeof(int) * nb_cmd);
	while (current)
	{
		if (current->next)
		{
			if (pipe(current->fd) == -1)
			{
				perror("pipe");
				return ;
			}
			else 
				printf("%s piped\n", current->cmd[0]);
		}
		// else
		printf("fds after piping fd[0] : %d fd[1] : %d\n", current->fd[0], current->fd[1]);
		printf("curr id: %d\n", current->id);
		if (current->id == 0)
			exec_command(current, data, FIRST_CMD, &i);
		else if (current->id == (nb_cmd - 1))
		{
			printf("\ncmd last: %s\nprevious fd[0] %d\nprevious fd[1] %d\n", current->cmd[0], current->prev->fd[0], current->prev->fd[1]);
			exec_command(current, data, LAST_CMD, &i);
		}
		else
			exec_command(current, data, MID_CMD, &i);
		printf("\ncmd: %s\nfd[0] %d\nfd[1] %d\n", current->cmd[0], current->fd[0], current->fd[1]);
		current = current->next;
	}
	close_all_pipes(data->cmds);
	wait_all(data);
	free(data->pids);
}
