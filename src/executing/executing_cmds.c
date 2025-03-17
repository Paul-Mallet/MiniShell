/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:30:24 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 11:53:37 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

static void	setup_pipes(t_cmd *cmds, t_cmd_order nbr)
{
	if (nbr == FIRST_CMD)
	{
		dup2(cmds->fd[1], STDOUT_FILENO);
		close(cmds->fd[0]);
		close(cmds->fd[1]);
	}
	else if (nbr == MID_CMD)
	{
		dup2(cmds->prev->fd[0], STDIN_FILENO);
		dup2(cmds->fd[1], STDOUT_FILENO);
		close(cmds->fd[0]);
		close(cmds->fd[1]);  
	}
	else if (nbr == LAST_CMD)
	{
		dup2(cmds->prev->fd[0], STDIN_FILENO);
		close(cmds->prev->fd[1]); 
	}
}

void	executing_command(t_cmd *cmds, char *path, t_data *data, t_cmd_order nbr)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_pipes(cmds, nbr);
	if (cmds->prev)
		close_pipes(cmds->prev);
	// if (cmds->prev && cmds->prev->fd[0] >= 0)
	// 	close(cmds->prev->fd[0]);
	// if (cmds->prev && cmds->prev->fd[1] >= 0)
	// 	close(cmds->prev->fd[1]);
	if (!cmds->cmd)
		exit(EXIT_FAILURE);
	if (is_builtins(cmds->cmd[0]))
	{
		ft_builtins(data, cmds);
		if (path)
		{
			free(path);
			path = NULL;
		}
	}
	else	
		execve(path, cmds->cmd, data->char_env);
	free_data(data);
	if (path)
		free(path);
	exit(EXIT_FAILURE);
}


void	executing_simple_cmd(t_data *data, char *path)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!data->cmds->cmd)
		return ;
	execve(path, data->cmds->cmd, data->char_env);
	perror("execve");
	free_data(data);
}
