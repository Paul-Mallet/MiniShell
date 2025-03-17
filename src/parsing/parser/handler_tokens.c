/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:23:54 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 18:37:09 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "parsing.h"

t_token	*handle_redirection(char **input)
{
	t_token	*token;
	char	*value;
	size_t	len;

	len = 1;
	if ((*input)[0] == (*input)[1])
		len = 2;
	value = extract_word(*input, len);
	if (!value)
		return (NULL);
	token = new_token(REDIR, UNKNOW_SUBTYPE, value);
	*input += len;
	return (token);
}

t_token	*handle_pipe(char **input)
{
	t_token	*token;
	char	*value;

	value = extract_word(*input, 1);
	if (!value)
		return (NULL);
	token = new_token(PIPE, UNKNOW_SUBTYPE, value);
	// free(value); invalid free 
	(*input)++;
	return (token);
}

t_token	*handle_word(char **input)
{
	t_token	*token;
	char	*value;
	size_t	len;

	len = get_word_length(*input);
	value = extract_word(*input, len);
	if (!value)
		return (perror("malloc"), NULL);
	token = new_token(WORD, UNKNOW_SUBTYPE, value);
	*input += len;
	return (token);
}

t_token	*handle_double_quotes(char **input)
{
	t_token	*token;
	char	*value;
	size_t	len;

	if (!input || !*input || **input != '"')
		return (NULL);
	len = get_double_quotes_length(*input);
	if (len == 0)
		return (NULL);
	value = extract_word(*input, len);
	if (!value)
		return (NULL);
	token = new_token(WORD, UNKNOW_SUBTYPE, value);
	*input += len;
	return (token);
}

t_token	*handle_single_quotes(char **input)
{
	t_token	*token;
	char	*value;
	size_t	len;

	if (!input || !*input || **input != '\'')
		return (NULL);
	len = get_single_quotes_length(*input);
	if (len == 0)
		return (NULL);
	value = extract_word(*input, len);
	if (!value)
		return (NULL);
	token = new_token(WORD, UNKNOW_SUBTYPE, value);
	*input += len;
	return (token);
}
