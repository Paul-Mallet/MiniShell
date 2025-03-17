/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:39:36 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 18:37:09 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

char	*go_to_home(t_env *env)
{
	t_env	*curr;
	char	*home;

	home = NULL;
	curr = env;
	while (curr)
	{ 
		if (ft_strcmp(curr->key, "HOME") == 0)
		{
			home = ft_strdup(curr->value);
			break ;
		}

		curr = curr->next;
	}
	return (home);
}

void	handle_oldpwd(t_env *env)
{
	t_env	*curr;
	char	path[PATH_BUFFER];

	curr = env;
	while (curr)
	{ 
		if (ft_strcmp(curr->key, "OLDPWD") == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(getcwd(path, PATH_BUFFER));
			break ;
		}
		curr = curr->next;
	}
}

void	handle_pwd(t_env *env)
{
	t_env	*curr;
	char	path[PATH_BUFFER];

	curr = env;
	while (curr)
	{ 
		if (ft_strcmp(curr->key, "PWD") == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(getcwd(path, PATH_BUFFER));
			break ;
		}
		curr = curr->next;
	}
}

void	ft_cd(t_env *env, char *path)
{
	if (!path)
		path = go_to_home(env);
	handle_oldpwd(env);
	if (chdir(path) == -1)
		perror("cd");
	handle_pwd(env);
}
