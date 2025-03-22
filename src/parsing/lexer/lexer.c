/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:00:32 by paul_mallet       #+#    #+#             */
/*   Updated: 2025/03/22 11:30:33 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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
			is_in_sgle = !is_in_sgle;
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
		add_history(data->input);
		printf("\" or \': invalid odd quotes\n");
		data->exit_code = 2;
		free(data->input);
		return (false);
	}
	return (true);
}
