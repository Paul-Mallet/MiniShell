/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:30:43 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/19 17:05:57 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

char	*expander(char *input, t_env *env)
{
	char	*res;
	int		i;

	i = 0;
	if (input[i] == '\'')
		return (input);
	res = ft_strdup(input); //?
	if (!res)
		return (NULL);
	i = 0;
	while (res[i])
	{
		if (res[i] == '$')
		{
			res = expand_single_var(res, i, env); //?
			if (!res)
				return (NULL);
			i = 0;
		}
		else
			i++;
	}
	return (res);
}

char	*expand_single_var(char *input, int i, t_env *env)
{
	char	*temp;
	int		start;

	i++;
	temp = NULL;
	// if (input[i] == '?')
	// {
		// temp = error_code();  // a implementer
		// if (!temp)
		// 	return (free(input), NULL);
		// input = replace_var(input, i - 1, i + 1, temp);
		// free(temp);
	// }
	if (ft_isalpha(input[i]) || input[i] == '_')
	{
		start = i;
		while (ft_isalnum(input[i]) || input[i] == '_')
			i++;
		temp = get_env_value(i, start, input, env);
		if (temp)
		{
			input = replace_var(input, start - 1, i, temp);
			free(temp);
		}
		else
			input = replace_var(input, start - 1, i, "");
	}
	return (input);
}

char	*get_env_value(int end, int start, char *input, t_env *env)
{
	char	*key;
	int		i;
	int		len;

	len = end - start;
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (start < end)
		key[i++] = input[start++];
	key[i] = '\0';
	while (env)
	{
		if (!strncmp(env->key, key, len) && env->key[len] == '\0')
		{
			free(key);
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	free(key);
	return (NULL);
}

char *replace_var(char *input, int start, int end, char *value)
{
    char	*res;
    int		i;
    int		j;
    int		k;

    res = malloc(sizeof(char) * (ft_strlen(input) - (end - start) + ft_strlen(value) + 1));
    if (!res)
        return (NULL);
    i = 0;
    j = 0;
    k = 0;
    while (i < start)
        res[k++] = input[i++];
    while (value[j])
        res[k++] = value[j++];
    i = end;
    while (input[i])
        res[k++] = input[i++];
    res[k] = '\0';
    free(input);
    return (res);
}
