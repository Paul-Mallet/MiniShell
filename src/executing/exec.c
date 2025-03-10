/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:26:39 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/10 15:24:05 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

void	exec(t_data *data)
{
	int		nb_cmd;
	char	**char_env;

	if (!data->cmds)
		return ;
	char_env = make_env(data->env);
	if (!char_env)
		return ;
	nb_cmd = count_cmds(data->cmds);
	printf("%d\n", nb_cmd);
	check_heredoc(data);
	if (!data->cmds->next)
	{
		if (is_builtins(data->cmds->cmd[0]))
			ft_builtins(data, data->cmds);
		else
			exec_simple_cmd(data, char_env);
	}
	else
		exec_multiple_cmds(data, char_env);
	while(data->cmds)
	{
		close_all_pipes(data->cmds);
		data->cmds = data->cmds->next;
	}
	free_strs(char_env);
}

void	exec_multiple_cmds(t_data *data, char **char_env)
{
	t_cmd	*current;

	current = data->cmds;
	while (current)
	{
		if (!current->prev)
			exec_first_cmd(current, char_env, data);
		else if (!current->next)
			exec_last_cmd(current, char_env, data);
		else
			exec_command(current, char_env, data);
		current = current->next;
	}
	wait_all(data);
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
