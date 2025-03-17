/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtype_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:09:37 by paul_mallet       #+#    #+#             */
/*   Updated: 2025/03/17 09:59:17 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"
#include "../../../includes/executing.h"

#define UNKNOWN_SUBTYPE -1

void	handle_token_redir(t_token *token)
{
	if (!ft_strcmp(token->value, ">>"))
		token->subtype = APPEND;
	else if (!ft_strcmp(token->value, "<<"))
		token->subtype = HEREDOC;
	else if (token->value[0] == '<')
		token->subtype = REDIR_INPUT;
	else if (token->value[0] == '>')
		token->subtype = REDIR_OUTPUT;
}

void	handle_token_word(t_token *current)
{
	if ((current->prev && current->prev->subtype == HEREDOC))
		current->subtype = DELIM;
	else if ((current->prev && current->prev->subtype == IS_SEPARATOR)
		&& (current->prev->prev && current->prev->prev->subtype == HEREDOC))
		current->subtype = DELIM;
	else if ((current->prev && current->prev->type == REDIR))
		current->subtype = FILES;
	else if ((current->prev && current->prev->subtype == IS_SEPARATOR)
		&& (current->prev->prev && current->prev->prev->type == REDIR))
		current->subtype = FILES;
	else
		current->subtype = ARG;
}

void	subtyping_tokens(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (current->type == PIPE)
			current->subtype = IS_PIPE;
		else if (current->type == REDIR)
			handle_token_redir(current);
		else if (current->type == SEPARATOR)
			current->subtype = IS_SEPARATOR;
		else if (current->type == WORD)
			handle_token_word(current);
		current = current->next;
	}
}
