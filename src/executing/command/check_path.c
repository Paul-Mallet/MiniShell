/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:24:29 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/21 18:23:42 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"

int	is_dir(char *path)
{
	struct stat	file_infos;
	char		*msg;

	if (stat(path, &file_infos))
	{
		msg = ft_strjoin("minishell: ", path);
		perror(msg);
		free(msg);
		return (-1);
	}
	if (S_ISDIR(file_infos.st_mode))
		return (1);
	return (0);
}

int	is_executable(t_data *data, char *cmd)
{
	if (is_dir(cmd) == -1)
	{
		data->exit_code = 127;
		return (0);
	}
	else if (access(cmd, F_OK) != 0)
	{
		perror("access");
		data->exit_code = 127;
		return (0);
	}
	else if (access(cmd, X_OK) != 0)
	{
		perror("access");
		data->exit_code = 126;
		return (0);
	}
	return (1);
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

//./ls -> until execve() + probably free t_env -> ls after not working
char	*check_path(t_data *data, char *cmd)
{
	char	**path_var;

	path_var = get_path_var(data->env);
	if (!path_var)
	{
		if (is_executable(data, cmd))
			return (cmd);
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
	{
		free_strs(path_var);
		if (is_executable(data, cmd))
			return (cmd);
		return (NULL);
	}
	if (ft_strlen(cmd) == 0)
	{
		free_strs(path_var);
		printf("minishell: %s: command not found\n", cmd);
		data->exit_code = 127;
		return (NULL);
	}
	return (find_path(data, path_var, cmd));
}
