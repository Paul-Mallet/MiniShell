/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:15:15 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/26 12:43:44 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executing.h"

void	fill_new_redir(t_token *tokens, t_redir *new)
{
	printf("SUBTYPE: %u\n", tokens->subtype);
	new->file = NULL;
	new->value = NULL;
	new->value = tokens->value;
	new->fd = -1;
    new->append = false;
    new->heredoc = false;
	new->delimiter = NULL;
	if (tokens->next && tokens->next->subtype == FILES)
		new->file = tokens->next->value;
	else if (tokens->next->next && tokens->next->next->subtype == FILES)
		new->file = tokens->next->next->value;
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
}

void	init_new_redir(t_token *tokens, t_cmd *new)
{
	t_token	*current;
	t_redir	*redir;

	tokens = to_pipe_or_last_token(tokens);
	current = tokens; //tokens->type = PIPE || last
	redir = NULL;
	while (current->prev) //handle 1rst token == redir
	{
		printf("SUBTYPE: %u\nPREV_VALUE: %s\n", current->subtype, current->prev->value);
		if (current->type == REDIR)
		{
			redir = malloc(sizeof(t_redir));
			if (!redir)
				printf("failed");
			fill_new_redir(current, redir);
			break ;
		}
		current = current->prev;
	}
	if (redir) //send NULL? to init
		new->redir = redir;
}

// t_redir	*new_redir(t_token *tokens)
// {
// 	t_redir	*new;

// 	new = (t_redir *)malloc(sizeof(t_redir));
// 	if (!new)
// 		return (NULL);
// 		    new->append = false;
// 	new->file = NULL;
// 	new->value = NULL;
// 	new->value = tokens->value;
// 	new->fd = -1;
// 	if (tokens->next && tokens->next->subtype == FILES)
// 		new->file = tokens->next->value;
// 	else if (tokens->next->next && tokens->next->next->subtype == FILES)
// 		new->file = tokens->next->next->value;
//     new->append = false;
//     new->heredoc = false;
// 	new->delimiter = NULL;
// 	if (tokens->subtype == APPEND)
// 		new->append = true;
// 	else if (tokens->subtype == HEREDOC)
// 	{
// 		new->heredoc = true;
// 		if (tokens->next && tokens->next->subtype == DELIM)
// 			new->delimiter = tokens->next->value;
// 		else if (tokens->next->next && tokens->next->next->subtype == DELIM)
// 			new->delimiter = tokens->next->next->value;
// 	}
// 	return (new);
// }