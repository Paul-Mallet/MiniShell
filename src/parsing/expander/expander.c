/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:30:21 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/21 16:30:41 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

char	*expand_variable(char *input, size_t *i, t_data *data)
{
	char	*key;
	char	*value;
	size_t	start;

	(*i)++;
	start = *i;
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(data->exit_code));
	}
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	key = ft_substr(input, start, *i - start);
	if (!key)
		return (NULL);
	value = get_key_value(data->env, key);
	free(key);
	return (value);
}

void	add_expanding(char **expanded, char *value, size_t *i, t_data *data)
{
	char	*new_value;
	char	*tmp;

	new_value = expand_variable(value, i, data);
	if (!new_value)
		return ;
	tmp = *expanded;
	*expanded = ft_strjoin(*expanded, new_value);
	free(tmp);
	free(new_value);
}

char	*expander(char *value, t_data *data)
{
	size_t	i;
	char	*expanded;
	bool	in_sngl;
	bool	in_double;

	i = 0;
	expanded = ft_strdup("");
	in_sngl = false;
	in_double = false;
	while (expanded && value[i])
	{
		if (value[i] == '\'' && !in_double)
			in_sngl = !in_sngl;
		if (value[i] == '\"' && !in_sngl)
			in_double = !in_double;
		if (value[i] == '$' && value[i + 1] && !in_sngl && value[i + 1] != ' ')
		{
			add_expanding(&expanded, value, &i, data);
			continue ;
		}
		add_index(&expanded, value[i]);
		i++;
	}
	free(value);
	return (expanded);
}
