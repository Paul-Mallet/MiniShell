/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:30:21 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/15 18:38:36 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

char	*expander(char *value, t_data *data)
{
	int			expand_len;
	t_expand	exp;

	exp.i = 0;
	exp.j = 0;
	expand_len = expand_length(value, data);
	return (expanding(value, data, expand_len, exp));
}

int	check_key(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*expanding(char *value, t_data *data, int len, t_expand exp)
{
	exp.res = (char *)malloc((len + 1) * sizeof(char));
	if (!exp.res)
		return (NULL);
	while (value[exp.i])
	{
		// if (value[exp.i] == '$' && value[exp.i + 1] && value[exp.i + 1] == '\'')
		// {
		// 	while (value[exp.i] != '\'')
		// 		exp.res[exp.j++] = value[exp.i++];
		// }
		if (value[exp.i] == '$' && value[exp.i + 1] && value[exp.i + 1] == '?')
		{
			exp.k = 0;
			exp.tmp = ft_itoa(data->exit_code);
			while (exp.tmp[exp.k])
				exp.res[exp.j++] = exp.tmp[exp.k++];
			free(exp.tmp);
		}
		else if (value[exp.i] == '$'
		&& value[exp.i + 1] && check_key(value[exp.i + 1]))
		{
			exp.k = 0;
			exp.tmp = get_key_value(value, exp.i, data);
			exp.i++;
			while (value[exp.i] && check_key(value[exp.i]))
				exp.i++;
			if (!exp.tmp)
				continue ;
			while (exp.tmp[exp.k])
				exp.res[exp.j++] = exp.tmp[exp.k++];
		}
		else
			exp.res[exp.j++] = value[exp.i++];
	}
	exp.res[exp.j] = '\0';
	return (exp.res);
}

char	*get_key_value(char *value, int i, t_data *data) 
{
	char	*key;
	t_env	*current;

	i++;
	current = data->env;
	if (ft_isalpha(value[i]) || value[i] == '_')
	{
		key = extract_key(value, i);
		while (current)
		{
			if (!ft_strcmp(current->key, key))
			{
				free(key);
				return (current->value);
			}
			current = current->next;
		}
		free(key);
	}
	return (NULL);
}