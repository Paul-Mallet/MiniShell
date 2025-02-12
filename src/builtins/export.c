/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:39:54 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/12 16:40:16 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void	update_env(t_env *env, char *value)
{
	free(env->value);
	env->value = ft_strdup(value);
}

void	add_env(char *import, t_env **env)
{
	t_env	*new_vrb;
	t_env	*tmp;

	new_vrb = new_env_node(import);
	if (!new_vrb)
		return;
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_vrb;
}

void	ft_export(char *import, t_env **env)
{
	char    *sep;
	char	*key;
	char	*value;
	t_env	*tmp;

	sep = ft_strchr(import, '=');
	if (!sep)
		return;
	key = ft_strndup(import, sep - import);
	value = ft_strdup(sep + 1);
	if (!key || !value)
		return (free_key_and_value(key, value));
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			update_env(tmp, value);
			return (free_key_and_value(key, value));
		}
		tmp = tmp->next;
	}
	add_env(import, env);
}

void	free_key_and_value(char *key, char *value)
{
	free(key);
	free(value);
}