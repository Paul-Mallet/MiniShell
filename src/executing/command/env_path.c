/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/20 12:54:34 by paul_mallet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"

int	is_dir(char *value)
{
	struct stat	file_infos;

	if (stat(value, &file_infos))
		return (-1);
	if (S_ISDIR(file_infos.st_mode))	
		return (1);
	return (0);
}

bool	is_executable(t_data *data, char *cmd, char **path_var)
{
	if (is_dir(cmd) == 1 && !path_var)
	{
		perror(cmd);
		data->exit_code = 126;
		return (false);
	}
	if (path_var)
		free_strs(path_var);
	if (access(cmd, F_OK) != 0)
	{
		perror(cmd);
		data->exit_code = 127;
		return (false);
	}
	if (access(cmd, F_OK) == 0 && !access(cmd, X_OK))
	{
		perror(cmd);
		data->exit_code = 126;
		return (false);
	}
	return (true);
}


char	*check_path(t_data *data, char *cmd)
{
	char	**path_var;

	path_var = get_path_var(data->env);
	if (!path_var)
	{
		if (is_executable(data, cmd, NULL))
			return (cmd);
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (is_executable(data, cmd, path_var))
			return (cmd);
		return (NULL);
	}
	return (find_path(data, path_var, cmd));
}


char	**get_path_var(t_env *env)
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

void	free_strs(char **paths)
{
	int		i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	paths = NULL;
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


char	*find_path(t_data *data, char **path_var, char *cmd)
{
	int		i;
	char	*path;
	int		found_path;

	i = 0;
	found_path = 0;
	while (path_var[i])
	{
		path = construct_path(path_var[i], cmd);
		if (path)
		{
			if (access(path, F_OK) == 0)
			{
				found_path = 1;
				if (is_executable(data, path, path_var))
					return (path);
				free(path);
				return (NULL);
				// if (access(path, X_OK) == 0)
				// {
				// 	free_strs(path_var);
				// 	return (path);
				// }
				// else
				// {
					// is_executable(data, path, path_var);
					// free(path);
					// printf("minishell: %s: Permission denied\n", path);
					// data->exit_code = 126;
					// free_strs(path_var);
					// return (NULL);
				// }
			}
			free(path);
		}
		i++;
	}
	if (!found_path)
		is_executable(data, path, path_var);
	return (NULL);
}
