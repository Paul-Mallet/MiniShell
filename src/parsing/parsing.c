/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/15 12:07:48 by paul_mallet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

/*
	reduce_spaces between words
*/
static char	*ft_reduce_spaces(char *input)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc((ft_strlen(input) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		while (!ft_isspace(input[i]) && input[i])
			str[j++] = input[i++];
		while (ft_isspace(input[i]) && input[i])
			i++;
		if (input[i])
			str[j++] = ' ';
	}
	str[j] = '\0';
	return (str);
}

/*
	parse input to be formatted with tokenizer
	* trim 1rst & last spaces
	* reduce to 1 between words
*/
char	*ft_parsing(char *input)
{
	char	*trimmed;

	trimmed = ft_strtrim(input, " \t\n\v\f\r");
	trimmed = ft_reduce_spaces(trimmed);
	return (trimmed);
}