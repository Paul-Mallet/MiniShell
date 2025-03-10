/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:00:32 by paul_mallet       #+#    #+#             */
/*   Updated: 2025/03/10 12:04:34 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

/*
	check if input is a full spaces string
*/
int	ft_isspaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	init_quotes(t_valid_quotes *quotes)
{
	quotes->sgle_cnt = 0;
	quotes->dble_cnt = 0;
	quotes->is_in_sgle = 0;
	quotes->is_in_dble = 0;
}

/*
	check if quotes in input are valid
	* single & double
	* amount of each, not count single in double
	* if odd amount, then error
	* if even, valid
*/
int	ft_valid_quotes(char *input)
{
	t_valid_quotes	quotes;

	init_quotes(&quotes);
	while (*input)
	{
		if (*input == '\"' && !quotes.is_in_sgle)
		{
			quotes.is_in_dble++;
			quotes.is_in_dble %= 2;
			quotes.dble_cnt++;
		}
		if (*input == '\'' && !quotes.is_in_dble)
		{
			quotes.is_in_sgle++;
			quotes.is_in_sgle %= 2;
			quotes.sgle_cnt++;
		}
		input++;
	}
	if ((quotes.sgle_cnt % 2 == 0) && (quotes.dble_cnt % 2 == 0))
		return (1);
	return (0);
}

void	ft_lexer(char *input)
{
	if (!input || ft_isspaces(input))
		return ;
	if (!ft_valid_quotes(input))
		error_handling(ERR_UNCLOSED_QUOTES, "\" or \'");
}
