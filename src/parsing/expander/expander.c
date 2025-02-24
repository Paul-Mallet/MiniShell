/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:30:21 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/24 18:24:51 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

char	*expander(char *value, t_env *env)
{
	int			expand_len;
	t_expand	expand;

	expand.i = 0;
	expand.j = 0;
	if (value[0] == '\'')
		return (value);
	expand_len = expand_length(value, env);
	return (expanding(value, env, expand_len, expand));
}

int	check_key(char c)
{
	return (ft_isalpha(c) || c == '_');
}

char	*expanding(char *value, t_env *env, int len, t_expand expand)
{
	expand.res = (char *)malloc(len + 1);
	if (!expand.res)
		return (NULL);
	while (value[expand.i])
	{
		if (value[expand.i] == '$'
		&& value[expand.i + 1] && check_key(value[expand.i + 1]))
		{
			expand.k = 0;
			expand.tmp = get_key_value(value, expand.i, env);
			expand.i++;
			while (value[expand.i] && ft_isalnum(value[expand.i]))
				expand.i++;
			if (!expand.tmp)
				continue ;
			while (expand.tmp[expand.k])
				expand.res[expand.j++] = expand.tmp[expand.k++];
		}
		else
			expand.res[expand.j++] = value[expand.i++];
	}
	expand.res[expand.j] = '\0';
	return (expand.res);
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
	}
	return (NULL);
}
