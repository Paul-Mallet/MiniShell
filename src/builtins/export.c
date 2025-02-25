/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:39:54 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/25 10:59:53 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include "../../includes/parsing.h"

void	export_env_var(t_env **env, char *import)
{
	t_env	*current;
	t_env	*new;
	char	*key;

	current = *env;
	key = extract_key(import, 0);
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0) //!
		{
			free (current->value);
			current->value = ft_strdup(ft_strchr(import, '=') + 1);
			return ;
		}
		else
			current = current->next;
	}
	new = new_env_node(import);
	if (new)
		env_add_back(env, new);
	free(key);
}

bool	check_key_fmt(char *value)
{
	int	i;
	bool	has_equal;

	i = 0;
	has_equal = false;
	if (!value || (!ft_isalpha(value[i]) && value[i] != '_'))
		return (false);
	while (value[i])
	{
		if (value[i] == '=')
		{
			has_equal = true;
			break;
		}
		else if (!ft_isalnum(value[i]) && value[i] != '_')
			return (false);
		i++;
	}
	return (has_equal);
}

bool	check_if_value(char *value)
{
	int	i;

	i = 0;
	while(value[i])
	{
		if (value[i] == '=' && value[i + 1])
			return (true);
		i++;
	}
	return (false);
}

void	ft_export(t_env *env, t_token *tokens)
{
	t_token	*current;

	if (!tokens->next)
	{
		print_env(env);
		return ;
	}
	current = tokens->next;
	while (current)
	{
		if (current->next && current->subtype == IS_SEPARATOR)
			current = current->next;
		else if (current->type == WORD)
		{
			if (check_key_fmt(current->value))
				export_env_var(&env, current->value);
			current = current->next;
		}
		else
			return ;
	}
}
