/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:28:40 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/15 15:26:10 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

t_token *handle_redirection(char **input)
{
	t_token *token;
	char *value;
	size_t len;

	len = 1;
	if ((*input)[0] == (*input)[1])
		len = 2;
	value = extract_word(*input, len);
	if (!value)
		return (NULL);
	token = new_token(REDIR, value);
	free(value);
	*input += len;
	return (token);
}

t_token *handle_pipe(char **input)
{
	t_token *token;
	char *value;

	value = extract_word(*input, 1);
	if (!value)
		return (NULL);
	token = new_token(PIPE, value);
	free(value);
	(*input)++;
	return (token);
}

t_token *handle_word(char **input)
{
	t_token *token;
	char *value;
	size_t len;

	len = get_word_length(*input);
	value = extract_word(*input, len);
	if (!value)
		return (NULL);
	token = new_token(WORD, value);
	free(value);
	*input += len;
	return (token);
}

t_token *init_tokens(char *input)
{
	t_token *tokens;
	t_token *new;

	tokens = NULL;
	while (*input)
	{
		if (*input == ' ')
		{
			new = new_token(SEPARATOR, " ");
			input++;
		}
		else if (is_redirection(*input))
			new = handle_redirection(&input);
		else if (is_pipe(*input))
			new = handle_pipe(&input);
		else
			new = handle_word(&input);
		if (!new)
		{
			free_token(&tokens);
			return (NULL);
		}
		token_add_back(&tokens, new);
	}
	return (tokens);
}
