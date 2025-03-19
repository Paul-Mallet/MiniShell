/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:30:24 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 14:44:14 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"
#include "signals.h"

static void	setup_pipes(t_cmd *cmds, t_cmd_order nbr)
{
	// printf("has_input: %d\n", cmds->has_input);
	// printf("has_output: %d\n", cmds->has_output);
	// if (nbr == FIRST_CMD)
	// {
	// 	printf("cmd : %s\n", cmds->cmd[0]);
	// 	printf("nbr == first_cmd\ninput %d\noutput %d\n", cmds->has_input, cmds->has_output);
	// 	printf("fd[0] = %d\nfd[1] = %d\n", cmds->fd[0], cmds->fd[1]);
	// }
	// else if (nbr == MID_CMD)
	// {
	// 	printf("cmd : %s\n", cmds->cmd[0]);
	// 	printf("nbr == mid_cmd\ninput %d\noutput %d\n", cmds->has_input, cmds->has_output);
	// 	printf("prev fd[0] = %d\nfd[1] = %d\n", cmds->prev->fd[0], cmds->fd[1]);
	// }
	// else if (nbr == LAST_CMD)
	// {
	// 	printf("cmd : %s\n", cmds->cmd[0]);
	// 	printf("nbr == last_cmd\ninput %d\noutput %d\n", cmds->has_input, cmds->has_output);
	// 	printf("prev fd[0] = %d\n", cmds->prev->fd[0]);
	// }
	if (nbr == FIRST_CMD)
	{
		// if (cmds->has_output == false)
			dup2(cmds->fd[1], STDOUT_FILENO);
		close(cmds->fd[0]);
		close(cmds->fd[1]);
	}
	else if (nbr == MID_CMD)
	{
		// if (!cmds->has_input == false)
			dup2(cmds->prev->fd[0], STDIN_FILENO);
		// if (!cmds->has_output == false)
			dup2(cmds->fd[1], STDOUT_FILENO);
		// close(cmds->prev->fd[1]);
		close(cmds->prev->fd[0]);
		close(cmds->prev->fd[1]);
		close(cmds->fd[1]);
		close(cmds->fd[0]);
	}
	else if (nbr == LAST_CMD)
	{
		// if (!cmds->has_input == false)
			dup2(cmds->prev->fd[0], STDIN_FILENO);
		close(cmds->prev->fd[0]);
		close(cmds->prev->fd[1]);
	}
}

void	executing_command(t_cmd *cmds, char *path, t_data *data, t_cmd_order nbr)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_pipes(cmds, nbr);
	close_all_pipes(data->cmds);
	if (is_builtins(cmds->cmd[0]))
	{
		ft_builtins(data, cmds);
		free_data(data);
		exit (1);
	}
	// if (cmds->prev)
		// close_pipes(cmds->prev);
	execve(path, cmds->cmd, data->char_env);
	perror("execve");
	if (path)
		free(path);
	free_data(data);
	exit(EXIT_FAILURE);
}

static void	free_simple_cmd(t_data *data)
{
	if (data->cmds)
		close_pipes(data->cmds);
	if (data->env)
		free_env(&data->env);
	free_processing(data);
}

void	executing_simple_cmd(t_data *data)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtins(data->cmds->cmd[0]))
	{
		ft_builtins(data, data->cmds);
		free_data(data);
		exit (1);
	}
	path = check_path(data, data->cmds->cmd[0]);
	if (!path)
	{
		free_simple_cmd(data);
		exit(data->exit_code);
	}
	if (!data->cmds->cmd)
		return ;
	execve(path, data->cmds->cmd, data->char_env);
	perror("execve");
	if (path)
		free(path);
	free_simple_cmd(data);
}
