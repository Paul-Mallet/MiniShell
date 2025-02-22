/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:44 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/22 18:03:30 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_echo(t_token *tokens)
{
	bool	arg_n;

	arg_n = false;
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
	if (!ft_echo_next(tokens, arg_n));
		return (0); 
	return (1);  // error a implementer
}

int	ft_echo_next(t_token *tokens, bool arg_n)
{
	bool	first_word;

	first_word = true;
	while (tokens)
	{
		if (tokens->next && tokens->subtype == IS_SEPARATOR)
		{
			if (!first_word)
				ft_printf("%s", tokens->value);
		}
		else
		{
			if (tokens->type != WORD)
			{
				printf("error");
				return (1); // error a implementer
			}
			ft_printf("%s", tokens->value);
			first_word = false;
		}
		tokens = tokens->next;
	}
	if (!arg_n)
		ft_printf("\n");
	return (0);
}
