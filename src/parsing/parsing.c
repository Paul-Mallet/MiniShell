/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/15 17:50:34 by abarahho         ###   ########.fr       */
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

void	ft_parsing(char *value, t_data *data)
{
	char	*trimmed;

	trimmed = ft_strtrim(value, " \t\n");
	data->tokens = first_tokenization(trimmed, data);
	second_tokenization(data);
	free(trimmed);
	// get_expanded(data->tokens, data);
	// remove_double_quotes(data->tokens);
	// remove_single_quotes(data->tokens);
}
