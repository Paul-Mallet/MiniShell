/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:39:36 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/10 12:13:12 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

char	*go_to_home(t_env *env)
{
	t_env	*current;
	char	*home;

	home = NULL;
	current = env;
	while (current)
	{ 
		if (ft_strcmp(current->key, "HOME") == 0)
		{
			home = ft_strdup(current->value);
			break ;
		}

		current = current->next;
	}
	return (home);
}

void	handle_oldpwd(t_env *env)
{
	t_env	*current;
	char	path[PATH_BUFFER];

	current = env;
	while (current)
	{ 
		if (ft_strcmp(current->key, "OLDPWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(getcwd(path, PATH_BUFFER));
			break ;
		}
		current = current->next;
	}
}

void	handle_pwd(t_env *env)
{
	t_env	*current;
	char	path[PATH_BUFFER];

	current = env;
	while (current)
	{ 
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(getcwd(path, PATH_BUFFER));
			break ;
		}
		current = current->next;
	}
}

void	ft_cd(t_env *env, char *path)
{
	if (!path)
		path = go_to_home(env);
	handle_oldpwd(env);
	handle_pwd(env);
	if (chdir(path) == -1)
		perror("cd");
	free(path);
}
