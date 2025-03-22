/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/20 17:25:14 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"

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

char	*is_executable_path(t_data *data, char *path, char **path_var)
{
	if (access(path, X_OK) == 0)
	{
		free_strs(path_var);
		return (path);
	}
	printf("minishell: %s: Permission denied\n", path);
	data->exit_code = 126;
	free(path);
	free_strs(path_var);
	return (NULL);
}

char	*find_path(t_data *data, char **path_var, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (path_var[i])
	{
		path = construct_path(path_var[i], cmd);
		if (path)
		{
			if (access(path, F_OK) == 0)
				return (is_executable_path(data, path, path_var));
			free(path);
		}
		i++;
	}
	printf("minishell: %s: command not found\n", cmd);
	data->exit_code = 127;
	free_strs(path_var);
	return (NULL);
}
