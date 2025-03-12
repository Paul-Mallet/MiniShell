/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:30:43 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/12 14:12:44 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

int	expand_length(char *value, t_data *data)
{
	int		i;
	int		total_len;
	int		var_len;
	char	*exit_str;

	i = 0;
	total_len = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] && value[i + 1] == '?')
		{
			exit_str = ft_itoa(data->exit_code);
			var_len = ft_strlen(exit_str);
			total_len += var_len;
			free (exit_str);
		}
		else if (value[i] == '$' && value[i + 1] && check_key(value[i + 1]))
		{
			var_len = get_value_len(value, i, data);
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

int	get_value_len(char *value, int i, t_data *data) 
{
	char	*key;
	t_env	*current;

	current = data->env;
	i++;
	if (ft_isalpha(value[i]) || value[i] == '_')
	{
		key = extract_key(value, i);
		while (current)
		{
			if (!ft_strcmp(current->key, key))
			{
				free(key);
				return (ft_strlen(current->value));
			}
			current = current->next;
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
