/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:24:29 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/24 13:53:48 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"

int	is_dir(char *path)
{
	struct stat	file_infos;

	if (stat(path, &file_infos) == -1)
		return (0);
	if (S_ISDIR(file_infos.st_mode))
	{
		ft_dprintf(2, "%s : is a directory\n", path);
		return (1);
	}
	return (0);
}

int	is_executable(t_data *data, char *cmd)
{
	if (is_dir(cmd) == 1)
	{
		data->exit_code = 127;
		return (0);
	}
	if (access(cmd, F_OK) != 0)
	{
		perror("access");
		data->exit_code = 127;
		return (0);
	}
	if (access(cmd, X_OK) != 0)
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

char	*check_path(t_data *data, char *cmd)
{
	char	**path_var;

	if ((cmd[0] == '.' && !cmd[1])
		|| (cmd[0] == '.' && cmd[1] == '.' && !cmd[2]))
		return (ft_dprintf(2, "%s : command not found", cmd), NULL);
	path_var = get_path_var(data->env);
	if (!path_var)
	{
		if (is_executable(data, cmd))
			return (cmd);
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (is_executable(data, cmd))
			return (free_strs(path_var), cmd);
		return (free_strs(path_var), NULL);
	}
	if (ft_strlen(cmd) == 0)
	{
		ft_dprintf(2, "minishell: %s: command not found\n", cmd);
		data->exit_code = 127;
		return (free_strs(path_var), NULL);
	}
	return (find_path(data, path_var, cmd));
}
