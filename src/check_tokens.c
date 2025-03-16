/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:18:28 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/16 18:05:28 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"
#include "../includes/executing.h"
#include "../includes/signals.h"

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
			&& current->next->next && current->next->next->type != WORD))
		{
			error_handling(SYNTAX_ERROR_NEAR_TOKEN, data->tokens->value);
			data->exit_code = 2;
			return (false);
		}
		current = current->next;
	}
	return (true);
}
