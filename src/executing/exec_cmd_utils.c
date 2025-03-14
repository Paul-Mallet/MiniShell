/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:30:24 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/14 17:49:16 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

void	executing_command(t_cmd *cmds, char *path, t_data *data)
{
	int	redir;
	
	redir = check_redir(cmds);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	printf("between redir: %d\n", redir);
	if (redir == 1)
		dup2(cmds->prev->fd[0], STDIN_FILENO);
	if (redir == 2)
		dup2(cmds->fd[1], STDOUT_FILENO);
	printf("between fd[0]: %d\n", cmds->fd[0]);
	printf("between fd[1]: %d\n", cmds->fd[1]);
	// close(cmds->prev->fd[0]);
	// close(cmds->fd[1]);
	// close(cmds->fd[0]);
	// close(cmds->fd[1]);
	// close(cmds->fd[0]);
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
	int	redir;
	
	redir = check_redir(cmds);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	printf("first redir: %d\n", redir);
	if (redir == 2)
		dup2(cmds->fd[1], STDOUT_FILENO);
	printf("first fd[0]: %d\n", cmds->fd[0]);
	printf("first fd[1]: %d\n", cmds->fd[1]);
	// close(cmds->fd[1]);
	// close(cmds->fd[0]);
	// close(cmds->fd[1]);
	if (!cmds->cmd)
		return ;
	if (is_builtins(cmds->cmd[0]))
		ft_builtins(data, cmds);
	else
	{
		execve(path, cmds->cmd, data->char_env);
		perror("execve");
		free_data_children(data);
	}
}

void	executing_last_cmd(t_cmd *cmds, char *path, t_data *data)
{
	int	redir;
	
	redir = check_redir(cmds);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	printf("last redir: %d\n", redir);
	printf("last prev fd[0]: %d\n", cmds->prev->fd[0]);
	printf("last prev fd[1]: %d\n", cmds->prev->fd[1]);
	if (redir == 1)
		dup2(cmds->prev->fd[0], STDIN_FILENO);
	printf("last fd[0]: %d\n", cmds->fd[0]);
	printf("last fd[1]: %d\n", cmds->fd[1]);
	// close(cmds->prev->fd[0]);
	// close(cmds->prev->fd[1]);
	// close(cmds->fd[0]);
	// close(cmds->fd[1]);
	if (!cmds->cmd)
		return ;
	if (is_builtins(cmds->cmd[0]))
		ft_builtins(data, cmds);
	else
	{
		execve(path, cmds->cmd, data->char_env);
		perror("execve");
		free_data_children(data);
	}
}

void	executing_simple_cmd(t_data *data, char *path)
{
	int	redir;

	printf("exec simple cmd\n");
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redir = check_redir(data->cmds);
	if (!data->cmds->cmd)
		return ;
	execve(path, data->cmds->cmd, data->char_env);
	perror("execve");
	free_data_children(data);
}
