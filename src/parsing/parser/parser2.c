/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:09:37 by paul_mallet       #+#    #+#             */
/*   Updated: 2025/02/16 20:01:26 by paul_mallet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

int is_delim(t_token *tokens)
{

}

t_token *second_tokenization(t_token *tokens)
{
	//handle_errors();
	while (tokens)
	{
		if ((tokens->type == WORD
			&& tokens->prev->prev->type == PIPE) || (tokens->type == WORD
			&& tokens->prev->prev->subtype != HEREDOC)) //|| nothing
			tokens->subtype = CMD;
		else if (tokens->type == WORD
			&& tokens->prev->prev->subtype == CMD)
			tokens->subtype = ARG;
			//fn to check arg(1rst '-', get 1rst then skip same char while finding another one...)
		else if (tokens->type == WORD
			&& tokens->next->next->type == REDIR) //not allowed HEREDOC & APPEND
			tokens->subtype = FILES;
		else if (tokens->value == '<'
			&& tokens->prev->prev->subtype == FILES)
			tokens->subtype = REDIR_INPUT;
		else if (tokens->value == '>'
			&& tokens->prev->prev->subtype == FILES)
			tokens->subtype = REDIR_OUTPUT;
		else if (tokens->type == REDIR
			&& tokens->value == ">>")
			tokens->subtype = APPEND;
		else if (tokens->type == REDIR
			&& !ft_strcmp(tokens->value, "<<"))
			tokens->subtype = HEREDOC;
		else if (tokens->type == WORD
			&& tokens->prev->prev->subtype == HEREDOC)
			tokens->subtype = DELIM;
		tokens = tokens->next;
	}
}
