/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:30:24 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/22 17:22:22 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"
#include "signals.h"

//export test=salut << a
void	setup_pipes(t_cmd *cmds, t_cmd_order nbr)
{
	if (nbr == FIRST_CMD)
	{
		if (!cmds->has_output)
			dup2(cmds->fd[1], STDOUT_FILENO);
		close(cmds->fd[0]);
		close(cmds->fd[1]);
	}
	else if (nbr == MID_CMD)
	{
		if (!cmds->has_input)
			dup2(cmds->prev->fd[0], STDIN_FILENO);
		if (!cmds->has_output)
			dup2(cmds->fd[1], STDOUT_FILENO);
		close(cmds->prev->fd[1]);
		close(cmds->prev->fd[0]);
		close(cmds->fd[1]);
		close(cmds->fd[0]);
	}
	else if (nbr == LAST_CMD)
	{
		if (!cmds->has_input)
			dup2(cmds->prev->fd[0], STDIN_FILENO);
		close(cmds->prev->fd[0]);
		close(cmds->prev->fd[1]);
	}
}

void	executing_command(t_cmd *cmds, t_data *data, t_cmd_order nbr)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_pipes(cmds, nbr);
	close_all_pipes(data->cmds);
	if (is_builtins(cmds->cmd[0]))
	{
		ft_builtins(data, cmds, false);
		free_pids(data);
		exit(EXIT_SUCCESS);
	}
	path = check_path(data, cmds->cmd[0]);
	if (!path)
	{
		free_pids(data);
		exit(data->exit_code);
	}
	data->char_env = make_env(data->env);
	execve(path, cmds->cmd, data->char_env);
	perror("execve");
	free(path);
	free_pids(data);
	exit(EXIT_FAILURE);
}

void	executing_simple_cmd(t_data *data)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = check_path(data, data->cmds->cmd[0]);
	if (!path)
	{
		free_data(data);
		exit(data->exit_code);
	}
	if (!data->cmds->cmd)
		return ;
	data->char_env = make_env(data->env);
	execve(path, data->cmds->cmd, data->char_env);
	perror("execve");
	if (path)
		free(path);
	free_data(data);
}
