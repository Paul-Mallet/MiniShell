/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/12 17:59:20 by abarahho         ###   ########.fr       */
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
		printf("%s", current->value);
		if (current->type == WORD && current->subtype != DELIM)
		{
			if (current->value[0] == '$' && current->value[1])
			{
				expansion = expander(current->value, data);
				if (expansion && ft_strcmp(expansion, current->value))
				{
					free(current->value);
					current->value = expansion;
				}
			}
			// free(current->value);
			// current->value = expansion;
		}
		current = current->next;
	}
}

void	ft_parsing(char *value, t_data *data)
{
	char	*trimmed;

	trimmed = ft_strtrim(value, " \t\n");
	data->tokens = first_tokenization(trimmed, data);
	free(trimmed);
	remove_empty_token(data->tokens);
	join_tokens(&data->tokens);
	remove_double_quotes(data->tokens);
	second_tokenization(data);
	get_expanded(data->tokens, data);
	remove_single_quotes(data->tokens);
}
