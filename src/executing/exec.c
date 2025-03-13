/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:26:39 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/13 14:20:40 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

int	exec(t_data *data)
{
	t_cmd	*current;

	// check_heredoc(data);
	if (!data->cmds)
		return (EXIT_FAILURE);
	current = data->cmds;
	data->char_env = make_env(data->env);
	if (!data->char_env)
		return (EXIT_FAILURE);
	if (current && !current->next)
	{
		if (is_builtins(current->cmd[0]))
			return (ft_builtins(data, data->cmds));
		else
			return (exec_simple_cmd(data));
	}
	return (exec_multiple_cmds(data));
}

int	exec_multiple_cmds(t_data *data)
{
	t_cmd	*current;

	current = data->cmds;
	while (current)
	{
		if (current && !current->prev)
		{
			if (exec_first_cmd(current, data))
				return (EXIT_FAILURE);
		}
		else if (current && !current->next)
		{
			if (exec_last_cmd(current, data))
				return (EXIT_FAILURE);
		}
		else if (current)
		{
			if (exec_command(current, data))
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	wait_all(data);
	return (EXIT_SUCCESS);
}

void	wait_all(t_data *data)
{
	int		status;
	int		pid;
	t_cmd	*current;

	current = data->cmds;
	while (current)
	{
		pid = waitpid(0, &status, 0);
		if (pid > 0)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
		}
		close_all_pipes(current);
		current = current->next;
	}
}

// void	exec(t_data *data)
// {
// 	t_cmd	*current;
// 	int		nb_cmd;

// 	print_cmd_struct(data->cmds);
// 	if (!data->cmds)
// 	{
// 		data->exit_code = 2;
// 		return ;
// 	}
// 	current = data->cmds;
// 	data->char_env = make_env(data->env);
// 	nb_cmd = count_cmds(data->cmds);
// 	check_heredoc(data);
// 	if (!current->next)
// 	{
// 		if (is_builtins(current->cmd[0]))
// 			ft_builtins(data, data->cmds);
// 		else
// 			exec_simple_cmd(data);
// 	}
// 	exec_multiple_cmds(data);
// }

// int	exec_multiple_cmds(t_data *data)
// {
// 	t_cmd	*current;

// 	current = data->cmds;
// 	while (current)
// 	{
// 		if (!current->prev)
// 			exec_first_cmd(current, data);
// 		else if (!current->next)
// 			exec_last_cmd(current, data);
// 		else
// 			exec_command(current, data);
// 		current = current->next;
// 	}
// 	wait_all(data);
// 	return (EXIT_SUCCESS);
// }

// void	wait_all(t_data *data)
// {
// 	int		status;
// 	int		pid;
// 	t_cmd	*current;

// 	current = data->cmds;
// 	while (current)
// 	{
// 		pid = waitpid(0, &status, 0);
// 		if (pid > 0)
// 		{
// 			if (WIFEXITED(status))
// 				data->exit_code = WEXITSTATUS(status);
// 		}
// 		close_all_pipes(current);
// 		current = current->next;
// 	}
// }
