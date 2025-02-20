/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:44 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/20 19:28:40 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_echo(t_token *tokens)
{
	bool	arg_n;
	bool	first_word;

	arg_n = false;
	first_word = true;
	tokens = tokens->next;
	while (tokens)
	{
		if (tokens && tokens->subtype == IS_SEPARATOR)
			tokens = tokens->next;
		if (tokens && !ft_strcmp(tokens->value, "-n"))
		{
			arg_n = true;
			tokens = tokens->next;
		}
		else
			break;
	}
	while (tokens)
	{
		if (tokens->next && tokens->subtype == IS_SEPARATOR)
		{
			if (!first_word)
				ft_printf("%s", tokens->value);
		}
		else
		{
			ft_printf("%s", tokens->value);
			first_word = false;
		}
		tokens = tokens->next;
	}
	if (!arg_n)
		ft_printf("\n");
}
