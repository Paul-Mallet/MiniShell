/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:01:48 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/12 18:06:52 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

void	remove_join_quotes(t_token *tokens, char c)
{
	char	*new_value;
	int		len;

	if (!tokens || !tokens->value)
		return ;
	len = len_without_qtes(tokens->value, c);
	new_value = malloc((len + 1) * sizeof(char));
	if (!new_value)
		return ;
	fill_without_quotes(new_value, tokens->value, c);
	free(tokens->value);
	tokens->value = NULL;
	tokens->value = new_value;
}

void	remove_single_quotes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current && current->type == WORD)
		{
			if (if_single_quotes(current->value))
				remove_join_quotes(current, '\'');
		}
		current = current->next;
	}
}
void	remove_double_quotes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current && current->type == WORD)
		{
			if (if_double_quotes(current->value))
				remove_join_quotes(current, '"');
		}
		current = current->next;
	}
}