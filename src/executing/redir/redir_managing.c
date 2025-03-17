/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:40:55 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 14:27:32 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executing.h"

bool	check_if_is_last_in(t_redir *redir)
{
	t_redir	*current;

	current = redir;
	while (current->next)
	{
		if ((current->next->heredoc || current->next->in_redir))
			return(false);
		current = current->next;
	}
	return (true);
}

bool	check_if_is_last_out(t_redir *redir)
{
	t_redir	*current;

	current = redir;
	while (current->next)
	{
		if ((current->next->append || current->next->out_redir))
			return(false);
		current = current->next;
	}
	return (true);
}

void	check_redir(t_cmd *cmds)
{
	t_redir	*current;
	bool	is_last_in;
	bool	is_last_out;

	if (!cmds->redir)
		return ;
	is_last_in = false;
	is_last_out = false;
	current = cmds->redir;
	while (current)
	{
		is_last_in = check_if_is_last_in(current);
		is_last_out = check_if_is_last_out(current);
		if (current->in_redir)
			redir_input(current, is_last_in);
		else if (current->out_redir)
			redir_output(current, is_last_out);
		else if (current->append)
			redir_append(current, is_last_in);
		else if (current->heredoc)
			redir_heredoc(current, is_last_out);
		current = current->next;
	}
}

