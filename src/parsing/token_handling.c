/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:44:18 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/13 10:01:12 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

void	remove_token(t_token *token)
{
	t_token	*current;

	current = token;
	if (current->prev && current->next)
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
	else if (token->prev && !current->next)
		current->prev->next = NULL;
	else if (!token->prev && current->next)
		current->next->prev = NULL;
	free(token);
}

void	remove_empty_token(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->value)
		{
			if (ft_strcmp(current->value, "\"\"") == 0 || ft_strcmp(current->value, "''") == 0)
			{
				free (current->value);
				current->value = ft_strdup("\0");
			}
		}
		current = current->next;
	}
}

void	join_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;
	char	*new_value;

	current = *tokens;
	new_value = NULL;
	while (current && current->next)
	{
		next = current->next;
		if (current->type == WORD && next->type == WORD)
		{
			new_value = ft_strjoin(current->value, next->value);
			if (!new_value)
				return ;
			free(current->value);
			free(next->value);
			next->value = new_value;
			if (current == *tokens)
				*tokens = next;
			remove_token(current);
		}
		current = next;
	}
}
