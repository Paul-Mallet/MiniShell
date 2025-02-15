/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:28:40 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/15 10:46:01 by paul_mallet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

/*
	check if input is an empty string
*/
ft_isempty(char *input)
{
	if (ft_strlen(input))
		return (0);
	return (1);
}

/*
	check if input is a full spaces string
*/
ft_isspaces(char *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]))
	{
		if (!ft_isspace(input[i]))
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
ft_valid_quotes(char *input)
{
	int sgle_cnt;
	int dble_cnt;
	int	is_in_dble;

	sgle_cnt = 0;
	dble_cnt = 0;
	is_in_dble = 0;
	while (*input)
	{
		if (*input == '\"')
		{
			is_in_dble++;
			is_in_dble %= 2;
			dble_cnt++;
		}
		if (*input == '\'' && !is_in_dble)
			sgle_cnt++;
		input++;
	}
	if ((sgle_cnt %2 == 0) && (dble_cnt %2 == 0))
		return (1);
	return (0);
}

void  ft_lexer(char *input)
{
	if (ft_isempty(input) || ft_isspaces(input))
		return ; //new readline(prompt);
	//if (!ft_valid_quotes(input))
		//error msg + exit
	//if (!ft_valid_pipes(input))
		//error msg + exit
	//if (!ft_valid_redir(input))
		//error_msg + exit
}
