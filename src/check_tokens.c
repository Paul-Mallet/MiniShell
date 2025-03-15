/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:18:28 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/15 15:18:53 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"
#include "../includes/executing.h"
#include "../includes/signals.h"

bool	check_tokens(t_data *data)
{
	if (!data->tokens)
		return (false);
	if (!data->tokens->next && data->tokens->subtype != ARG)
	{
		error_handling(SYNTAX_ERROR_NEAR_TOKEN, data->tokens->value);
		data->exit_code = 2;
		return (false);
	}
	return (true);
}
