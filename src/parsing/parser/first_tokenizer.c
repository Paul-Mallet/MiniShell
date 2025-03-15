/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:28:40 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/15 18:28:32 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

t_token	*handle_exit_code(char **input, t_data *data)
{
	t_token	*token;
	char	*value;

	if (!input || !*input)
		return (NULL);
	printf("exit_code: %d\n", data->exit_code);
	value = ft_itoa(data->exit_code);
	if (!value)
		return (NULL);
	token = new_token(WORD, UNKNOW_SUBTYPE, value);
	(*input) += 2;
	return (token);
}

t_token	*process_token(char **input)
{
	t_token	*new;

	new = NULL;
	// if (**input == '$' && *(*input + 1) && *(*input + 1) != '?')
	// 	*input = check_expanding(*input, data);
	// if (**input == '$' && *(*input + 1) && *(*input + 1) == '?')
	// 	new = handle_exit_code(input, data);
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

char	*check_expanding(char *input, t_data *data)
{
	char	*key_value;
	
	key_value = get_key_value(input, 0, data);
	if (key_value)
		return (input);
	input++;
	if (*input && (ft_isalpha(*input) || *input == '_'))
		input++;
	while (*input && check_key(*input))
		input++;
	if (*input && *input == ' ')
		input++;
	return (input);
}
