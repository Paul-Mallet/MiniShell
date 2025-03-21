/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:43:45 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/21 17:09:19 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	set_env_values(t_env *new, char *entry, char *sep)
{
	if (sep)
	{
		new->key = ft_strndup(entry, sep - entry);
		new->value = ft_strdup(sep + 1);
	}
	else
	{
		new->key = ft_strndup(entry, ft_strlen(entry) - 1);
		new->value = ft_strdup("");
	}
}

t_env	*new_env_node(char *entry)
{
	t_env	*new;
	char	*sep;

	*sep = NULL;
	if (!entry)
		return (NULL);
	if (check_if_value(entry))
		sep = ft_strchr(entry, '=');
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	set_env_values(new, entry, sep);
	new->next = NULL;
	if (!new->key)
	{
		free(new->key);
		free(new->value);
		free(new);
		return (NULL);
	}
	return (new);
}

void	env_add_back(t_env **env, t_env *new)
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

t_env	*import_env(char **env)
{
	t_env	*head;
	t_env	*new;
	int		i;

	if (!env)
		return (NULL);
	head = new_env_node(env[0]);
	if (!head)
		return (NULL);
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
		env_add_back(&head, new);
		i++;
	}
	return (head);
}

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !(*env))
		return ;
	current = *env;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*env = (NULL);
}
