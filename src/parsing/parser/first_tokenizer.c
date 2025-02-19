/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:28:40 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/19 12:08:20 by abarahho         ###   ########.fr       */
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
	token = new_token(REDIR, UNKNOW_SUBTYPE, value);
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
	token = new_token(PIPE, UNKNOW_SUBTYPE, value);
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
	if (len == 0)
		return (NULL);
	value = extract_word(*input, len);
	if (!value)
		return (NULL);
	token = new_token(WORD, UNKNOW_SUBTYPE, value);
	free(value);
	*input += len;
	return (token);
}

t_token *handle_double_quotes(char **input)
{
	t_token *token;
	char *value;
	size_t len;

	if (!input || !*input || **input != '"')
		return (NULL);
	len = get_double_quotes_length(*input);
	if (len == 0)
		return (NULL);
	value = extract_word(*input, len);
	if (!value)
		return (NULL);
	token = new_token(WORD, UNKNOW_SUBTYPE, value);
	free(value);
	*input += len;
	return (token);
}

t_token *handle_single_quotes(char **input)
{
	t_token *token;
	char *value;
	size_t len;

	if (!input || !*input || **input != '\'')
		return (NULL);
	len = get_single_quotes_length(*input);
	if (len == 0)
		return (NULL);
	value = extract_word(*input, len);
	if (!value)
		return (NULL);
	token = new_token(WORD, UNKNOW_SUBTYPE, value);
	free(value);
	*input += len;
	return (token);
}

t_token *first_tokenization(char *input) //rename
{
	t_token *tokens;
	t_token *new;

	tokens = NULL;
	while (*input)
	{
		if (*input == '\"')
			new = handle_double_quotes(&input);
		else if (*input =='\'')
			new = handle_single_quotes(&input);
		else if (*input == ' ')
		{
			while (*input == ' ' && *(input + 1) == ' ')
				input++;
			new = new_token(SEPARATOR, UNKNOW_SUBTYPE, " ");
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
