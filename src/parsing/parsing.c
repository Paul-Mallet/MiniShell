/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/17 11:32:41 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

void	get_expanded(t_token *tokens, t_data *data)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->subtype == ARG || current->subtype == FILES)
			current->value = expander(current->value, data);
		current = current->next;
	}
}

void	quoteless(char *token)
{
	int		j;
	int		i;
	bool	in_single;
	bool	in_double;

	i = 0;
	j = 0;
	in_single = false;
	in_double = false;
	while (token[i])
	{
		if (!in_single && token[i] == '\"')
			in_double = !in_double;
		else if (!in_double && token[i] == '\'')
			in_single = !in_single;
		else if ((in_single && token[i] != '\'')
			|| (in_double && token[i] != '\"')
			|| (!in_double && !in_single))
		{
			token[j] = token[i];
			j++;
		}
		i++;
	}
	token[j] = 0;
}

void	remove_quotes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == WORD)
			quoteless(current->value);
		current = current->next;
	}
}

static bool	check_whitespace(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while(current)
	{
		if (current->type == REDIR)
			return (true);
		if (current->subtype == ARG && !ft_isspaces(current->value))
			return (true);
		current = current->next;
	}
	return (false);
}

bool	ft_parsing(char *value, t_data *data)
{
	char	*trimmed;

	trimmed = ft_strtrim(value, " \t\n");
	data->tokens = first_tokenization(trimmed);
	if (!check_tokens(data))
		return (free_processing(data), false);
	free(trimmed);
	join_tokens(&data->tokens);
	subtyping_tokens(data);
	get_expanded(data->tokens, data);
	remove_quotes(data->tokens);
	if (!check_whitespace(data->tokens))
		return (free_processing(data), false);
	return (true);
}

