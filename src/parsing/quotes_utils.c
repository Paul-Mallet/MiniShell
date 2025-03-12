/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:10:45 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/12 18:06:14 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

bool	if_double_quotes(char *value)
{
	int	i;

	i = 0;
	while(value[i])
	{
		if (value[i] == '"')
			return (true);
		i++;
	}
	return (false);
}

bool	if_single_quotes(char *value)
{
	int	i;

	i = 0;
	while(value[i])
	{
		if (value[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

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

