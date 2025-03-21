/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/21 18:17:57 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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

bool	ft_parsing(char *value, t_data *data)
{
	char	*trimmed;

	trimmed = ft_strtrim(value, " \t\n");
	data->tokens = first_tokenization(trimmed);
	free(trimmed);
	if (!check_tokens(data))
		return (free_parsing(data), false);
	join_tokens(&data->tokens);
	subtyping_tokens(data);
	get_expanded(data->tokens, data);
	remove_quotes(data->tokens);
	return (true);
}
