/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:39:34 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/11 19:30:12 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;


char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] && len < n)
		len++;
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

t_env	*create_env_node(char *entry)
{
	t_env	*new;
	char	*sep;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	sep = strchr(entry, '=');
	if (!sep)
	{
		free(new);
		return (NULL);
	}
	new->key = ft_strndup(entry, sep - entry);
	new->value = strdup(sep + 1);
	if (!new->key || !new->value)
	{
		free(new->key);
		free(new->value);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_env	*import_env(char **env)
{
	t_env	*head;
	t_env	*new;
	t_env	*tmp;

	head = NULL;
	while (*env)
	{
		new = create_env_node(*env);
		if (!head)
			head = new;
		else
		{
			tmp = head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		env++;
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

int	main(int ac, char **av, char **env)
{
	t_env	*our_env;

	(void)ac;
	(void)av;
	our_env = import_env(env);
	while (our_env)
	{
		printf("%s=%s\n", our_env->key, our_env->value);
		our_env = our_env->next;
	}
	free_env(our_env);
	return (0);
}
