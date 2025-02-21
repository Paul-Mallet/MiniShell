/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:44:18 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/21 14:32:21 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

bool	is_dollar(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

void	remove_token(t_token *token)
{
	if (token->prev && token->next)
	{
		token->prev->next = token->next;
		token->next->prev = token->prev;
	}
	else if (token->prev && !token->next)
		token->prev->next = NULL;
	else if (!token->prev && token->next)
		token->next->prev = NULL;
	free(token);
}

int	check_cmd_tokens(t_token *tokens)
{
	t_token	*current;
	bool	cmd_expected;

	current = tokens;
	cmd_expected = true;
	while (current)
	{
		if (cmd_expected)
		{
			if (current->subtype == CMD)
				cmd_expected = false;
			else if (current->subtype != IS_SEPARATOR)
			{
				printf("command not found %s\n", current->value);
				return (0);
			}
		}
		if (current->subtype == IS_PIPE)
			cmd_expected = true;
		current = current->next;
	}
	return (1);
}

