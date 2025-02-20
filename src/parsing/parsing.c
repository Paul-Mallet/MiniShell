/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/20 12:39:12 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

static void	get_expanded(t_token *tokens, t_env *env)
{
	char	**paths;
	t_token	*current;
	char	*expansion;

	paths = get_path_vrbl(env);
	current = tokens;
	expansion = NULL;
	while (current)
	{
		if (current->type == WORD && current->subtype != DELIM)
		{
			expansion = expander(current->value, env);
			if (ft_strcmp(expansion, current->value))
				free(current->value);
			current->value = expansion;
		}
		current = current->next;
	}
}

t_token	*ft_parsing(char *input, t_env *env)
{
	char	*trimmed;
	t_token	*tokens;

	(void)env;
	trimmed = ft_strtrim(input, " \t\n");
	tokens = first_tokenization(trimmed);
	free(trimmed);
	second_tokenization(tokens, env);
	get_expanded(tokens, env);
	return (tokens);
}