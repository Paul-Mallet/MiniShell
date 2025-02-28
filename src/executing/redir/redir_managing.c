/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:40:55 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/28 15:02:18 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executing.h"

void	redir_managing(t_data *data)
{
	t_cmd	*current;

	current = data->cmds;
	while (current)
	{
		if (!check_redir(current))
			data->exit_code = 1; // error
		current = current->next;
	}
}

int	check_redir(t_cmd *cmd)
{
	t_redir	*current;
	bool	last_cmd;

	last_cmd = false;
	current = cmd->redir;
	while (current)
	{
		if (!current->next)
			last_cmd = true;
		if (current->in_redir)
		{
			if (redir_input(current, last_cmd));
			return (0);
		}
		else if (current->out_redir)
		{
			if (redir_output(current, last_cmd));
			return (0);
		}
		else if (current->heredoc)
		{
			if (redir_heredoc(current, last_cmd));
			return (0);
		}
		else if (current->append)
		{
			if (redir_append(current, last_cmd));
			return (0);
		}
		current = current->next;
	}
	return (1);
}
