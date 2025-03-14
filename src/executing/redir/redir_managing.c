/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:40:55 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/14 15:48:47 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executing.h"

// bool	redir_managing(t_cmd *cmds)
// {
// 	t_cmd	*current;

// 	current = cmds;
// 	while (current)
// 	{
// 		if (!check_redir(current))
// 			return (false);
// 		current = current->next;
// 	}
// 	return (true);
// }

bool	check_if_is_last_in(t_redir *redir)
{
	t_redir	*current;
	int		nb_redir;

	nb_redir = 0;
	current = redir;
	while (current)
	{
		if ((current->heredoc || current->in_redir))
			nb_redir++;
		current = current->next;
	}
	if (nb_redir == 1)
		return (true);
	return (false);
}

bool	check_if_is_last_out(t_redir *redir)
{
	t_redir	*current;
	int		nb_redir;

	nb_redir = 0;
	current = redir;
	while (current)
	{
		if ((current->append || current->out_redir))
			nb_redir++;
		current = current->next;
	}
	if (nb_redir == 1)
		return (true);
	return (false);
}

int	redir_managing(t_cmd *cmds)
{
	t_redir	*current;
	bool	is_last_in;
	bool	is_last_out;
	int		is_redirected;

	if (!cmds->redir)
		return(false);
	is_last_in = false;
	is_last_out = false;
	current = cmds->redir;
	while (current)
	{
		is_last_in = check_if_is_last_in(current);
		is_last_out = check_if_is_last_out(current);
		if (current->in_redir)
			is_redirected = redir_input(current, is_last_in);
		else if (current->out_redir)
			is_redirected = redir_output(current, is_last_out);
		else if (current->append)
			is_redirected = redir_append(current, is_last_in);
		else if (current->heredoc)
			is_redirected = redir_heredoc(current, is_last_out);
		current = current->next;
	}
	if (!is_last_in)
		is_redirected = 1;
	else if (!is_last_out)
		is_redirected = 2;
	return (is_redirected);
}

