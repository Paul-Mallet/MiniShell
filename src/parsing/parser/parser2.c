/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:09:37 by paul_mallet       #+#    #+#             */
/*   Updated: 2025/02/16 13:28:57 by paul_mallet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

int is_delim(t_token *tokens)
{

}

t_token *second_tokenization(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == REDIR && tokens->value == ">>")
			tokens->subtype = APPEND;
		else if (tokens->type == REDIR && tokens->value == "<<")
			tokens->subtype = HEREDOC;
		else if (tokens->type == WORD
			&& tokens->prev->subtype == SEPARATOR
			&& tokens->prev->prev->subtype == HEREDOC)
			tokens->subtype = DELIM;
		tokens = tokens->next;
	}
}