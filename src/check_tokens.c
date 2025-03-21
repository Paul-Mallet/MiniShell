/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:18:28 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/21 17:17:45 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"
#include "executing.h"
#include "signals.h"

bool	check_token_syntax_1(t_token *current)
{
	if (!current->next && current->type != WORD)
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			current->value);
		return (false);
	}
	if (current->type == REDIR && current->next
		&& current->next->type != WORD && current->next->type != SEPARATOR)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (false);
	}
	return (true);
}

bool	check_token_syntax_2(t_token *current)
{
	if (ft_strcmp(current->value, "\\") == 0
		|| ft_strcmp(current->value, ";") == 0)
	{
		printf("minishell: '%s': not interpreted special chars\n",
			current->value);
		return (false);
	}
	if ((current->type == PIPE && current->next && current->next->type == PIPE)
		|| (current->type == PIPE && current->next->next
			&& current->next->next->type == PIPE))
	{
		printf("minishell: syntax error near unexpected token `||'\n");
		return (false);
	}
	return (true);
}

bool	check_tokens(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (!check_token_syntax_1(current))
			return (false);
		if (!check_token_syntax_2(current))
			return (false);
		current = current->next;
	}
	return (true);
}
