/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:30:43 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/24 18:23:02 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

int	expand_length(char *value, t_env *env)
{
	int		i;
	int		total_len;
	int		var_len;

	i = 0;
	total_len = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] && check_key(value[i + 1]))
		{
			var_len = get_value_len(value, i, env);
			total_len += var_len;
			i++;
			while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
				i++;
		}
		else
		{
			total_len++;
			i++;
		}
	}
	return (total_len);
}

int	get_value_len(char *value, int i, t_env *env) 
{
	char	*key;

	i++;
	if (ft_alnum(value[i]) || value[i] == '_')
	{
		key = extract_key(value, i);
		while (env)
		{
			if (!ft_strcmp(env->key, key))
			{
				free(key);
				return (ft_strlen(env->value));
			}
			env = env->next;
		}
		free (key);
	}
	return (0);
}

char	*extract_key(char *value, int i)
{
	int		j;
	char	*key;

	j = i;
	while (value[j] && check_key(value[j]))
		j++;
	key = ft_substr(value, i, j - i);
	return (key);
}
