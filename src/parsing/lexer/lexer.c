/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:00:32 by paul_mallet       #+#    #+#             */
/*   Updated: 2025/02/18 18:58:52 by abarahho         ###   ########.fr       */
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

/*
	check if quotes in input are valid
	* single & double
	* amount of each, not count single in double
	* if odd amount, then error
	* if even, valid
*/
int	ft_valid_quotes(char *input)
{
	int sgle_cnt;
	int dble_cnt;
	int	is_in_sgle;
	int	is_in_dble;

	sgle_cnt = 0;
	dble_cnt = 0;
	is_in_sgle = 0;
	is_in_dble = 0;
	while (*input)
	{
		if (*input == '\"' && !is_in_sgle)
		{
			is_in_dble++;
			is_in_dble %= 2;
			dble_cnt++;
		}
		if (*input == '\'' && !is_in_dble)
		{
			is_in_sgle++;
			is_in_sgle %= 2;
			sgle_cnt++;
		}
		input++;
	}
	if ((sgle_cnt % 2 == 0) && (dble_cnt % 2 == 0))
		return (1);
	return (0);
}

void	ft_lexer(char *input, t_error_code code)
{
	(void)code;
	if (!input || ft_isspaces(input))
		return ;
	// if (!ft_valid_quotes(input))
	// 	error_handling(code);
}