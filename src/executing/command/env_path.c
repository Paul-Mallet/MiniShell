/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/12 13:49:53 by abarahho         ###   ########.fr       */
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
		i++;
	}
	free(paths);
}

char	*construct_path(char *dir, char *cmd)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, cmd);
	free(temp);
	return (path);
}

char	*find_path(char **paths, char *cmd)
{
	int		i;
	char	*road;

	if (!cmd)
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
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, "PATH", 4) == 0)
			return (ft_split(current->value, ':'));
		current = current->next;
	}
	return (NULL);
}
