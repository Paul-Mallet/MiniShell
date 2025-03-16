/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:42:51 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/16 16:46:33 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

char	*extract_key(char *value, int i)
{
	int		j;
	char	*key;

	j = i;
	while (ft_isalnum(value[i]) || value[i] == '_')
		j++;
	key = ft_substr(value, i, j - i);
	return (key);
}

void	add_index(char **expanded, char i)
{
	char	*tmp;
	char 	*index;

	index = malloc(sizeof(char) * 2);
	index[0] = i;
	index[1] = '\0';

	tmp = *expanded;
	*expanded = ft_strjoin(*expanded, index);
	free(tmp);
	free(index);
}

char	*get_key_value(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (current->value)
				return (ft_strdup(current->value));
			else
				return (ft_strdup(""));
		}
		current = current->next;
	}
	return (ft_strdup(""));
}