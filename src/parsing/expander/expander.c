/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:30:43 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/21 18:40:22 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

char	*expander(char *value, t_env *env)
{
	//len
	//str
}

int	expand_length(char *value, t_env *env)
{
	int		i;
	int		total_len;
	int		var_len;

	i = 0;
	total_len = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] && 
			(ft_isalnum(value[i + 1]) || value[i + 1] == '_'))
		{
			var_len = get_vrbl_len(value, i, env);
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

int	get_vrbl_len(char *value, int i, t_env *env) 
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
				return (ft_strlen(env->value));
			}
			env = env->next;
		}
		free (key);
		return (0);
	}
	return (0);
}
char	*extract_key(char *value, int i)
{
	int		j;
	char	*key;

	j = i;
	while (value[j] && (ft_isalnum(value[j]) || value[j] == '_'))
		j++;
	key = ft_substr(value, i, j - i);
	return (key);
}

//----------------------------------------------------------------------

int	get_key_len(char *value_from_env_key)
{
	int	len;

	len = 0;
	while (*value_from_env_key && *value_from_env_key != '$') //no quotes
	{
		len++;
		value_from_env_key++;
	}
	return (len);
}

int	have_value(t_env *env, char *value, int i)
{
	char	*key;

	key = extract_key(value, i);
	if (!key)
		return (NULL);
	while (env)
	{
		if (!strcmp(env->key, key))
			return (1);
		env->next;
	}
	free(key);
	return (0);
}

int	skip_expand_key(char *value_from_env_key)
{
	int	i;
	
	i = get_key_len(value_from_env_key);
	return (i);
}

void	replace_expand_value(char *res, t_env *env)
{
	int		i;
	int		j;
	int		total_len;
	int		var_len;

	i = 0;
	total_len = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] && 
			(ft_isalnum(value[i + 1]) || value[i + 1] == '_'))
		{
			var_len = get_vrbl_len(value, i, env);
			total_len += var_len;
			i++;
			while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
				i++;
		}
		else
			res[j++] = value[i++];
	}
}


char	*expanded_input(char *value, t_env *env, int len)
{
	int		i;
	char	*res;

	res = (char *)malloc((len + 1)* sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (value[i] == '\$' && (ft_isalpha(value[i + 1]) || value[i + 1] == '_'))
		{
			if (have_value(env, value, i + 1)) //jump '$', until find $ or '\0'
				replace_expand_value(res, env);
			i += skip_expand_key(&value[i + 1]); //"$USERx$USER" -> "$USER" -> "pamallet"
		}
		else
		{
			res[i] = value[i];
			i++;
		}
	}
	res[len] = '\0';
	return (res);
}
