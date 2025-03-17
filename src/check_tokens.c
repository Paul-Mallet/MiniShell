/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:18:28 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 18:35:38 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "builtins.h"
#include "parsing.h"
#include "executing.h"
#include "signals.h"

bool	check_tokens(t_data *data)
{
	t_token	*current;

	if (!data->tokens)
		return (false);
	current = data->tokens;
	while (current)
	{
		if ((!current->next && current->type != WORD)
			|| (current->type == REDIR && current->next
			&& ((current->next->type != WORD && current->next->type != SEPARATOR)
			|| (current->type == REDIR && current->next->next
			&& current->next->next->type != WORD))))
		{
			error_handling(SYNTAX_ERROR_NEAR_TOKEN, data->tokens->value);
			data->exit_code = 2;
			return (false);
		}
		current = current->next;
	}
	return (true);
}
