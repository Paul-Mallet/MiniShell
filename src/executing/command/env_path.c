/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/26 17:37:47 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"
#include "../../../includes/parsing.h"

void	free_strs(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		paths[i] = NULL;
		i++;
	}
	free (paths);
}

char	*construct_path(char *dir, char *cmd)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(dir, "/");
	path = NULL;
	if (temp)
	{
		path = ft_strjoin(temp, cmd);
		free(temp);
	}
	// free(temp);
	return (path);
}

char	*find_path(char **paths, char *cmd)
{
	int		i;
	char	*road;

	if (!paths || !cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		road = construct_path(paths[i], cmd);
		if (road && access(road, X_OK) == 0)
			return (road);
		free(road);
		i++;
	}
	return (NULL);
}

char	**get_path_vrbl(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
			return (ft_split(env->value, ':'));
		env = env->next;
	}
	return (NULL);
}
