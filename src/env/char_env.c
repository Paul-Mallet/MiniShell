/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:56:05 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/21 16:57:31 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"

static char	**malloc_char_env(t_env *env)
{
	t_env	*current;
	char	**char_env;
	int		i;

	current = env;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	char_env = (char **)malloc(sizeof(char *) * (i + 1));
	return (char_env);
}

char	**make_env(t_env *env)
{
	t_env	*current;
	char	**char_env;
	char	*tmp;
	int		i;

	char_env = malloc_char_env(env);
	if (!char_env)
		return (NULL);
	tmp = NULL;
	i = 0;
	current = env;
	while (current)
	{
		tmp = ft_strjoin(current->key, "=");
		char_env[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		i++;
		current = current->next;
	}
	char_env[i] = NULL;
	return (char_env);
}
