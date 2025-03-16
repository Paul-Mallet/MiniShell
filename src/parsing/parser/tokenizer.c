/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:28:40 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/16 16:55:17 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

t_token	*process_token(char **input)
{
	t_token	*new;

	new = NULL;
	if (**input == '\'')
		new = handle_single_quotes(input);
	else if (**input == '\"')
		new = handle_double_quotes(input);
	else if (**input == ' ')
	{
		while (**input == ' ' && *(*input + 1) == ' ')
			(*input)++;
		new = new_token(SEPARATOR, UNKNOW_SUBTYPE, ft_strdup(" "));
		(*input)++;
	}
	else if (is_redirection(**input))
		new = handle_redirection(input);
	else if (is_pipe(**input))
		new = handle_pipe(input);
	else
		new = handle_word(input);
	return (new);
}

t_token	*first_tokenization(char *input)
{
	t_token	*tokens;
	t_token	*new;

	tokens = NULL;
	while (*input)
	{
		new = process_token(&input);
		if (!new)
			return (free_tokens(&tokens), NULL);
		token_add_back(&tokens, new);
	}
	return (tokens);
}

