/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:43:45 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/14 14:29:29 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

t_env   *new_env_node(char *entry)
{
	t_env   *new;
	char    *sep;

	if (!entry)
		return (NULL);
	sep = ft_strchr(entry, '=');
	if (!sep)
		return (NULL);
	new = (t_env*)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strndup(entry, sep - entry);
	new->value = ft_strdup(sep + 1);
	new->is_env = 1;
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

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*curr;

	if (!env || !new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
	curr = *env;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}

t_env   *import_env(char **env)
{
	t_env   *head;
	t_env   *new;
	int     i; 
	
	if (!env)
		return (NULL);
	head = new_env_node(env[0]);
	if (!head)
		return (NULL) ;
	i = 1;
	while (env[i])
	{
		new = new_env_node(env[i]);
		if (!new)
		{
			free(new->key);
			free(new->value);
			free_env(&head);
			break ;
		}
		ft_envadd_back(&head, new);
		i++;
	}
	return (head);
}

void free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

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
	*env = (NULL);
}
