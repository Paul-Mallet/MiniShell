/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:30:43 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/20 10:30:25 by abarahho         ###   ########.fr       */
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
	res = ft_strdup(input);
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
			i ++;
		}
		i++;
	}
	return (res);
}

char	*expand_single_var(char *input, int i, t_env *env)
{
	char	*temp;
	int		start;
	int		end;
	char	quote;

	i++;
	temp = NULL;
	start = i;
	// if ((res[i] == '$') && !ft_isalpha(input[i + 1]))
	// {
		// temp = error_code();  // a implementer
		// if (!temp)
		// 	return (free(input), NULL);
		// input = replace_var(input, i - 1, i + 1, temp);
		// free(temp);
	// }
	if (input[i] == '\'' || input[i] == '"')
	{
		quote = input[i];
		i++;
		while (input[i] && input[i] != quote)
			i++;
		if (input[i] == quote)
			i++;
		temp = ft_substr(input, start, i - start);
		if (temp)
		{
			input = replace_var(input, start - 1, i, temp);
			free(temp);
		}
	}
	else if (ft_isalpha(input[i]) || input[i] == '_')
	{
		while (ft_isalnum(input[i]) || input[i] == '_')
			i++;
		end = i;
		temp = get_env_value(end, start, input, env);
		if (temp)
		{
			input = replace_var(input, start - 1, end, temp);
			free(temp);
		}
		else
			input = replace_var(input, start - 1, end, "");
	}
	return (input);
}

char	*get_btw_quotes(char *input, int i)
{
	char	quote;
	int		start;
	int		len;
	
	quote = input[i];
	start = i + 1;
	i = start;
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
		return (ft_strdup(""));
	len = i - start;
	return (ft_substr(input, start, len));
}

char	*get_env_value(int end, int start, char *input, t_env *env)
{
	char	*key;
	char	*value;

	key = ft_substr(input, start, end - start);
	if (!key)
		return (NULL);
	
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			value = ft_strdup(env->value);
			free(key);
			return (value);
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
