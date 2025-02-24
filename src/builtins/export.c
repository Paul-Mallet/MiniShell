/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:39:54 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/24 19:04:36 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

//new_node, add_back et free in lst_export.c
//print_env(t_env *env);

void	update_exp(t_export *export, char *value)
{
	free(export->value);
	export->value = ft_strdup(value);
}

void	update_key_env(t_env *current, char *key, char *value)
{
	free(current->value);
	if (!value)
		current->value = ft_strdup("");
	else
		current->value = ft_strdup(value);
}

void	export_env_var(t_env **env, char *import)
{
	char	*sep;
	char	*key;
	char	*value;
	t_env	*current;
	t_env	*new;

	sep = NULL;
	if (check_key_fmt(import))
	{
		sep = ft_strchr(import, '=');
		key = ft_strndup(import, sep - import);
	}
	value = ft_strdup(sep + 1);
	if (!key) //value can be ""
		return (free_key_and_value(key, value)); //stop
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (ft_strchr(import, '=')) //have key && value
				update_key_env(current, key, value);
			return ;
		}
		current = current->next;
	}
	new = new_exp_node(import); //not find = new = create + add back
	env_add_back(env, new);
}

bool	check_key_fmt(char *value)
{
	int	i;

	i = 0;
	if (!ft_isalpha(value[i]) || value[i] != '_')
		return (false);
	while(value[i] || value[i] == '=')
	{
		if (!ft_isalnum(value[i]) || value[i] != '_')
			return (false);
		i++;
	}
	return (true);
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

void	ft_export(t_token *tokens, t_env *env)
{
	t_token	*current;

	if (!tokens->next->next)
	{
		print_env(env);
		return ;
	}
	current = tokens->next;
	while (current)
	{
		if (tokens->next && tokens->subtype == IS_SEPARATOR)
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

void	free_key_and_value(char *key, char *value)
{
	free(key);
	free(value);
}
