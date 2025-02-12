/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:39:34 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/12 11:45:11 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

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

// int main(int ac, char **av, char **envp)
// {
// 	t_env   *our_env;

// 	(void)ac;
// 	(void)av;

// 	our_env = import_env(envp);
// 	print_env(our_env);
// 	free_env(our_env);
	
// 	return (0);
// }
