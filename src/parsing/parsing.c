/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/19 11:38:26 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

/*
	parse input to be formatted with tokenizer
	* trim 1rst & last spaces
	* reduce to 1 between words
*/
// static bool	check_input(char *str)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '"')
// 			count++;
// 		i++;
// 	}
// 	if ((count % 2) != 0)
// 		return (true);
// 	return (false);
// }

t_token	*ft_parsing(char *input, t_env *env)
{
	char	*trimmed;
	t_token	*tokens;

	(void)env;
	trimmed = ft_strtrim(input, " \t\n");
	// if (check_input(trimmed))
	// {
	// 	ft_printf("invalid");                                    mauvaise gestion d'erreur, verifier seulement double quotes hors singles quotes
	// 	exit (0);
	// }
	tokens = first_tokenization(trimmed);
	second_tokenization(tokens, env);
	free(trimmed);
	return (tokens);
}