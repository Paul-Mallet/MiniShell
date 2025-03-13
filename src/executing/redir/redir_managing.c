/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:40:55 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/13 11:20:04 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executing.h"

bool	redir_managing(t_cmd *cmds)
{
	t_cmd	*current;

	if (!cmds->redir)
		return (true);
	current = cmds;
	while (current)
	{
		if (!check_redir(current))
			return (false);
		current = current->next;
	}
	return (true);
}

bool	check_redir(t_cmd *cmds)
{
	t_redir	*current;
	bool	last_cmd;

	last_cmd = false;
	current = cmds->redir;
	while (current)
	{
		if (!current->next)
			last_cmd = true;
		if (current->in_redir)
		{
			if (redir_input(current, last_cmd) && last_cmd)
				return (true);
		}
		else if (current->out_redir)
		{
			if (redir_output(current, last_cmd) && last_cmd)
				return (true);
		}
		else if (current->append)
		{
			if (redir_append(current, last_cmd) && last_cmd)
				return (true);
		}
		else if (current->heredoc)
		{
			if (redir_heredoc(current, last_cmd) && last_cmd)
				return (true);
		}
		current = current->next;
	}
	return (false);
}
