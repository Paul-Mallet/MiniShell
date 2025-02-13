/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:41:49 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/13 14:02:53 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
# include "../../includes/builtins.h"

t_env   *new_env_node(char *entry)
{
	t_env   *new;
	char    *sep;

	sep = ft_strchr(entry, '=');
	if (!sep)
		return (NULL);
	new = (t_env*)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strndup(entry, sep - entry);
	new->value = ft_strdup(sep + 1);
	new->next = NULL;
	if (!new->key || !new->value)
	{
		free(new->key);
		free(new->value);
		free(new);
		return (NULL);
	}
	return (new);
}

t_env   *import_env(char **env)
{
	t_env   *head;
	t_env   *new;
	t_env   *tmp;
	int     i; 
	
	head = NULL;
	i = 0;
	while (env[i])
	{
		new = new_env_node(env[i]);
		if (new)
		{
			if (!head)
				head = new;
			else
			{
				tmp = head;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new;
			}
		}
		i++;
	}
	return (head);
}

void ft_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
