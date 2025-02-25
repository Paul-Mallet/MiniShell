/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:15:15 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/25 15:08:25 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executing.h"

t_redir	*new_redir(t_token *tokens)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
		    new->append = false;
	new->file = NULL;
	new->value = NULL;
	new->value = tokens->value;
	new->fd = -1;
	if (tokens->next && tokens->next->subtype == FILES)
		new->file = tokens->next->value;
	else if (tokens->next->next && tokens->next->next->subtype == FILES)
		new->file = tokens->next->next->value;
    new->append = false;
    new->heredoc = false;
	new->delimiter = NULL;
	if (tokens->subtype == APPEND)
		new->append = true;
	else if (tokens->subtype == HEREDOC)
	{
		new->heredoc = true;
		if (tokens->next && tokens->next->subtype == DELIM)
			new->delimiter = tokens->next->value;
		else if (tokens->next->next && tokens->next->next->subtype == DELIM)
			new->delimiter = tokens->next->next->value;
	}
	return (new);
}

// t_redir	*new_redir(void)
// {
// 	t_redir	*redir;

// 	redir = (t_redir *)malloc(sizeof(t_redir));
// 	if (!redir)
// 		return (NULL);
// 	redir->file = NULL;
// 	redir->value = NULL;
// 	redir->append = false;
// 	redir->heredoc = false;
// 	redir->delimiter = NULL;
// 	redir->next = NULL;
// 	return (redir);
// }

// void	redir_add_back(t_redir **lst, t_redir *new)
// {
// 	t_redir	*current;

// 	if (!lst || !new)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	current = *lst;
// 	while (current->next != NULL)
// 		current = current->next;
// 	current->next = new;
// 	new->prev = current;
// }

// void free_redir(t_redir **redirs)
// {
// 	t_redir *current;
// 	t_redir *next;

// 	if (!redirs || !*redirs)
// 		return;
// 	current = *redirs;
// 	while (current)
// 	{
// 		next = current->next;
// 		free(current->file);
// 		free(current->delimiter);
// 		free(current);
// 		current = next;
// 	}
// 	*redirs = NULL;
// }

// t_redir	*init_redirs(t_token **tokens)
// {
// 	t_redir *head;
// 	t_redir *new;
// 	t_token	*current;

// 	head = NULL;
// 	current = *tokens;
// 	while(current && current->subtype != IS_PIPE) //stop PIPE
// 	{
//         if (current->type == REDIR)
// 		{
// 		    new = new_redir(*tokens);
// 			redir_add_back(&head, new);
// 		}
// 		current = current->next;
// 	}
// 	return (head);
// }