/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:40:55 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/25 12:28:24 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"

bool	check_if_is_last_in(t_redir *redir, t_cmd *cmd)
{
	t_redir	*current;
	t_redir	*last_input;

	last_input = NULL;
	current = cmd->redir;
	while (current)
	{
		if (current->heredoc || current->in_redir)
		{
			cmd->has_input = true;
			last_input = current;
		}
		current = current->next;
	}
	return (redir == last_input);
}

bool	check_if_is_last_out(t_redir *redir, t_cmd *cmd)
{
	t_redir	*current;
	t_redir	*last_output;

	last_output = NULL;
	current = cmd->redir;
	while (current)
	{
		if (current->append || current->out_redir)
		{
			cmd->has_output = true;
			last_output = current;
		}
		current = current->next;
	}
	return (redir == last_output);
}

bool	check_redir(t_cmd *cmds, t_data *data)
{
	t_redir	*current;
	bool	is_last_in;
	bool	is_last_out;
	bool	check_is_valid;

	check_is_valid = true;
	current = cmds->redir;
	while (current)
	{
		is_last_in = check_if_is_last_in(current, cmds);
		is_last_out = check_if_is_last_out(current, cmds);
		if (current->in_redir)
			check_is_valid = redir_input(current, is_last_in, data);
		else if (current->out_redir)
			check_is_valid = redir_output(current, is_last_out, data);
		else if (current->append)
			check_is_valid = redir_append(current, is_last_out, data);
		else if (current->heredoc)
			redir_heredoc(current, is_last_in);
		if (!check_is_valid)
			return (check_is_valid);
		current = current->next;
	}
	return (true);
}
