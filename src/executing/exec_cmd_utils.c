/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:30:24 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/13 14:16:19 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

void	executing_command(t_cmd *cmds, char *path, t_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!redir_managing(cmds))
	{
		data->exit_code = 1;
		return ;
	}
	dup2(cmds->prev->fd[0], STDIN_FILENO);
	dup2(cmds->fd[1], STDOUT_FILENO);
	close(cmds->prev->fd[0]);
	close(cmds->fd[1]);
	if (!cmds->cmd)
		return ;
	if (is_builtins(cmds->cmd[0]))
		ft_builtins(data, cmds);
	else
		execve(path, cmds->cmd, data->char_env);
	perror("execve");
	free_data_children(data);
}

void	executing_first_cmd(t_cmd *cmds, char *path, t_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!redir_managing(cmds))
	{
		data->exit_code = 1;
		return ;
	}

	dup2(cmds->fd[1], STDOUT_FILENO);
	close(cmds->fd[0]);
	close(cmds->fd[1]);
	if (!cmds->cmd)
		return ;
	if (is_builtins(cmds->cmd[0]))
		ft_builtins(data, cmds);
	else
		execve(path, cmds->cmd, data->char_env);
	perror("execve");
	free_data_children(data);
}

void	executing_last_cmd(t_cmd *cmds, char *path, t_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmds->prev)
	{
		dup2(cmds->prev->fd[0], STDIN_FILENO);
		close(cmds->prev->fd[0]);
	}
	if (!redir_managing(cmds))
	{
		data->exit_code = 1;
		return ;
	}
	if (!cmds->cmd)
		return ;
	if (is_builtins(cmds->cmd[0]))
		ft_builtins(data, cmds);
	else
		execve(path, cmds->cmd, data->char_env);
	perror("execve");
	free_data_children(data);
}

void	executing_simple_cmd(t_data *data, char *path)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!redir_managing(data->cmds))
	{
		data->exit_code = 1;
		return ;
	}
	if (!data->cmds->cmd)
		return ;
	execve(path, data->cmds->cmd, data->char_env);
	perror("execve");
	free_data_children(data);
}
