/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:39:34 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/12 10:30:35 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"

typedef struct s_env
{
	char            *key;
	char            *value;
	struct s_env    *next;
}   t_env;

t_env   *create_env_node(char *entry)
{
	t_env   *new;
	char    *sep;

	sep = ft_strchr(entry, '=');
	if (!sep)
		return (NULL);

	new = malloc(sizeof(t_env));
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
	t_env   *head = NULL;
	t_env   *new;
	t_env   *tmp;
	int     i = 0;

	while (env[i])
	{
		new = create_env_node(env[i]);
		if (!new)
		{
			i++;
			continue;
		}

		if (!head)
			head = new;
		else
		{
			tmp = head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		i++;
	}
	return (head);
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

void print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void unset_env(t_env **env, char *key)
{
	t_env   *tmp = *env;
	t_env   *prev = NULL;

	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_env   *our_env;

	(void)ac;
	(void)av;

	our_env = import_env(envp);
	print_env(our_env);
	free_env(our_env);
	
	return (0);
}
