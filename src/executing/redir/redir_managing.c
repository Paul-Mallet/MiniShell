/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:40:55 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 19:31:43 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"

bool	check_if_is_last_in(t_redir *redir, t_cmd *cmds)
{
	t_redir	*current;

	current = redir;
	while (current->next)
	{
		if ((current->next->heredoc || current->next->in_redir))
			return(false);
		current = current->next;
	}
	cmds->has_input = true;
	return (true);
}

bool	check_if_is_last_out(t_redir *redir, t_cmd *cmds)
{
	t_redir	*current;

	current = redir;
	while (current->next)
	{
		if ((current->next->append || current->next->out_redir))
			return(false);
		current = current->next;
	}
	cmds->has_output = true;
	return (true);
}

void	check_redir(t_cmd *cmds, t_data *data)
{
	t_redir	*current;
	bool	is_last_in;
	bool	is_last_out;

	if (!cmds->redir)
		return ;
	current = cmds->redir;
	while (current)
	{
		is_last_in = check_if_is_last_in(current, cmds);
		is_last_out = check_if_is_last_out(current, cmds);
		if (current->in_redir)
			redir_input(current, is_last_in, data);
		else if (current->out_redir)
			redir_output(current, is_last_out, data);
		else if (current->append)
			redir_append(current, is_last_in, data);
		else if (current->heredoc)
			redir_heredoc(current, is_last_out, data);
		current = current->next;
	}
}

