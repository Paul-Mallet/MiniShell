/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:30:21 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/22 11:52:53 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

char	*expander(char *value, t_env *env)
{
	int	len = expand_length(value, env);
	printf("%s", expand(value, env, len));
	return (expand(value, env, len));
}

char	*expand(char *value, t_env *env, int len)
{
	char 	*tmp;
	char	*res;
	int		i;
	int		j;
	int		k;

	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] && 
			(ft_isalnum(value[i + 1]) || value[i + 1] == '_'))
		{
			k = 0;
			tmp = get_key_value(value, i, env);
			i++;
			while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
				i++;
			if (!tmp)
				continue ;
			while (tmp[k])
				res[j++] = tmp[k++];
		}
		else
			res[j++] = value[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*get_key_value(char *value, int i, t_env *env) 
{
	char	*key;

	i++;
	if (ft_isalpha(value[i]) || value[i] == '_')
	{
		key = extract_key(value, i);
		while (env)
		{
			if (!ft_strcmp(env->key, key))
			{
				free(key);
				return (env->value);
			}
			env = env->next;
		}
		free (key);
		return (NULL);
	}
	return (NULL);
}

