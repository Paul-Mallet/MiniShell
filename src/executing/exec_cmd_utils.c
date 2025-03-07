/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:30:24 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/07 18:30:44 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

void	executing_command(t_cmd *cmds, char *path, char **char_env, t_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redir_managing(cmds);
	dup2(cmds->prev->fd[0], STDIN_FILENO);
	dup2(cmds->fd[1], STDOUT_FILENO);
	close(cmds->prev->fd[0]);
	close(cmds->fd[1]);
	if (is_builtins(cmds->cmd[0]))
		ft_builtins(data, cmds);
	else
		execve(path, cmds->cmd, char_env);
	perror("execve");
}

void	executing_first_cmd(t_cmd *cmds, char *path, char **char_env, t_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2(cmds->fd[1], STDOUT_FILENO);
	close(cmds->fd[0]);
	close(cmds->fd[1]);
	redir_managing(cmds);
	if (is_builtins(cmds->cmd[0]))
		ft_builtins(data, cmds);
	else
		execve(path, cmds->cmd, char_env);
	perror("execve");
}

void	executing_last_cmd(t_cmd *cmds, char *path, char **char_env, t_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmds->prev)
	{
		dup2(cmds->prev->fd[0], STDIN_FILENO);
		close(cmds->prev->fd[0]);
	}
	redir_managing(cmds);
	if (is_builtins(cmds->cmd[0]))
		ft_builtins(data, cmds);
	else
		execve(path, cmds->cmd, char_env);
	perror("execve");
}

void	executing_simple_cmd(t_data *data, char *path, char **char_env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redir_managing(data->cmds);
	execve(path, data->cmds->cmd, char_env);
	perror("execve");
}
