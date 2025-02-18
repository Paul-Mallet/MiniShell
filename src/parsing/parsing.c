/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/17 23:21:04 by paul_mallet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

/*
	reduce_spaces between words
	! not between "", and '' !
*/
static char	*ft_reduce_spaces(char *input)
{
	char	*str;
	int		i;
	int		j;
	int		quote;

	str = (char *)malloc((ft_strlen(input) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && quote == 0)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		str[j++] = input[i++];
		if (!quote)
		{
			while (ft_isspace(input[i]) && input[i])
				i++;
			if (input[i] && !ft_isspace(str[j - 1]))
				str[j++] = ' ';
		}
		// while (!ft_isspace(input[i]) && input[i])
		// 	str[j++] = input[i++];
		// while (ft_isspace(input[i]) && input[i])
		// 	i++;
		// if (input[i])
		// 	str[j++] = ' ';
	}
	str[j] = '\0';
	return (str);
}

/*
	parse input to be formatted with tokenizer
	* trim 1rst & last spaces
	* reduce to 1 between words
*/
t_token	*ft_parsing(char *input)
{
	char	*trimmed;
	char	*reduced;
	t_token	*tokens;

	trimmed = ft_strtrim(input, " \t\n\v\f\r"); //"  ...   "
	reduced = ft_reduce_spaces(trimmed); //". . ."
	tokens = first_tokenization(trimmed);
	free(trimmed);
	free(reduced);
	//tokens = second_tokenization(tokens);
	return (tokens);
}