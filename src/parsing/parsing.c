/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/15 18:43:51 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

void	get_expanded(t_token *tokens, t_data *data)
{
	t_token	*current;
	char	*expansion;

	current = tokens;
	expansion = NULL;
	while (current)
	{
		if (current->subtype == ARG && current->subtype != DELIM)
		{
			expansion = expander(current->value, data);
			free(current->value);
			current->value = expansion;
		}
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

void	ft_parsing(char *value, t_data *data)
{
	char	*trimmed;

	trimmed = ft_strtrim(value, " \t\n");
	data->tokens = first_tokenization(trimmed);
	free(trimmed);
	join_tokens(&data->tokens);
	second_tokenization(data);
	// get_expanded(data->tokens, data); A REFAIRE single quote
	/*
		check whitespace tokens
	*/
	remove_quotes(data->tokens);
}
