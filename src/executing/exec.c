/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:26:39 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/07 11:43:10 by abarahho         ###   ########.fr       */
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
		exec_simple_cmd(data, char_env);
	else
		exec_multiple_cmds(data, char_env);
}

void	exec_multiple_cmds(t_data *data, char **char_env)
{
	t_cmd	*current;

	current = data->cmds;
	while (current)
	{
		if (!current->prev)
			exec_first_cmd(current, char_env, data->env);
		else if (!current->next)
			exec_last_cmd(current, char_env, data->env);
		else
			exec_command(current, char_env, data->env);
		current = current->next;
	}
	wait_all(data);
	free_strs(char_env);
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
		if (current->fd[0] != -1)
			close(current->fd[0]);
		if (current->fd[1] != -1)
			close(current->fd[1]);
		current = current->next;
	}
}
