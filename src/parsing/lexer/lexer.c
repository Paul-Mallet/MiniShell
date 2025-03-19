/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:00:32 by paul_mallet       #+#    #+#             */
/*   Updated: 2025/03/19 16:03:19 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/*
	check if input is a full spaces string
*/
int	ft_isspaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
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
bool	ft_valid_quotes(char *input)
{
	bool	is_in_dble;
	bool	is_in_sgle;

	is_in_dble = 0;
	is_in_sgle = 0;
	while (*input)
	{
		if (*input == '\"' && !is_in_sgle)
			is_in_dble = !is_in_dble;
		if (*input == '\'' && !is_in_dble)
			is_in_sgle = !is_in_sgle;;
		input++;
	}
	return (!is_in_dble && !is_in_sgle);
}

bool	ft_lexer(t_data *data)
{
	if (ft_isspaces(data->input))
		return (free(data->input), false);
	if (!ft_valid_quotes(data->input))
	{
		error_handling("\" or \'");
		data->exit_code = 2;
		add_history(data->input);
		free(data->input);
		return (false);
	}
	return (true);
}
