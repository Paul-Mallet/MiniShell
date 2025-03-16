/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/16 19:03:31 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"
#include "../../../includes/parsing.h"

bool	is_executable(char *cmd, t_data *data)
{
	if (access(cmd, F_OK) != 0)
	{
		perror("access");
		data->exit_code = 127;
		return (false);
	}
	if (is_dir(cmd))
	{
		printf("%s is a directory\n", cmd);
		data->exit_code = 126;
		return (false);
	}
	if (access(cmd, X_OK) != 0)
	{
		printf("No premissions\n");
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
		if (is_executable(cmd, data))
			return (cmd);
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (is_executable(cmd, data))
			return (cmd);
		return (NULL);
	}
	return (find_path(data, path_var, cmd));
}

char	*find_path(t_data *data, char **path_var, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (path_var[i])
	{
		path = construct_path(path_var[i], cmd);
		if (path && access(path, X_OK) == 0)
		{
			is_executable(path, data);
			free_strs(path_var);
			return (path);
		}
		free(path);
		i++;
	}
	free_strs(path_var);
	data->code = 127;
	error_handling(ERR_CMD_NOT_FOUND, cmd);
	return (NULL);
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

bool	is_dir(char *value)
{
	struct stat	file_infos;

	if (stat(value, &file_infos))
		return (-1);
	if (S_ISDIR(file_infos.st_mode))	
		return (1);
	return (0);
}

// int	is_cmd(char **paths, char *cmd, t_data *data)
// {
// 	int		i;
// 	char	*road;

// 	if (!paths)
// 	{
// 		if (is_executable(cmd, data))
// 			return (1);
// 		return (0);
// 	}
// 	if (ft_strchr(cmd, '/'))
// 	{
// 		if (is_executable(cmd, data))
// 			return (1);
// 		return (0);
// 	}
// 	i = 0;
// 	while (paths[i])
// 	{
// 		road = construct_path(paths[i], cmd);
// 		if (access(road, F_OK) == 0)
// 		{
// 			is_executable(road, data);
// 			free(road);
// 			return (1);
// 		}
// 		free(road);
// 		i++;
// 	}
// 	data->code = 127;
// 	return (0);
// }


