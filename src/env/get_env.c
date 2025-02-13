/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:43:45 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/13 10:54:51 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

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
		free_env(&env);
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
		new = new_env_node(env[i], env);
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

void free_env(t_env **env)
{
	t_list	*tmp;
	t_list	*next;

	if (env == NULL)
		return ;
	tmp = *env;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*env = NULL;
}
