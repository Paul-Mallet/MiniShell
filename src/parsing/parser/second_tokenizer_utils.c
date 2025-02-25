/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenizer_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:02 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/25 17:31:45 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

bool	is_cmd(char **paths, char *cmd)
{
	int		i;
	char	*road;
	struct stat	file_infos;

	if (cmd && ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0 && stat(cmd, &file_infos) == 0 && S_ISREG(file_infos.st_mode))
			return (true);
		return (false);
	}
	if (!paths || !cmd)
		return (false);
	i = 0;
	while (paths[i])
	{
		road = construct_path(paths[i], cmd);
		if (road && access(road, X_OK) == 0 && stat(road, &file_infos) == 0 && S_ISREG(file_infos.st_mode))
		{
			free(road);
			return (true);
		}
		free(road);
		i++;
	}
	return (false);
}

int	is_file(char *value)
{
	struct stat	file_infos;

	if (stat(value, &file_infos))
		return (-1);
	if (S_ISREG(file_infos.st_mode))
		return (1);
	return (0);
}

int	is_dir(char *value)
{
	struct stat	file_infos;

	if (stat(value, &file_infos))
		return (-1);
	if (S_ISDIR(file_infos.st_mode))	
		return (1);
	return (0);
}

int	is_builtins(char *cmd)
{
	if (strcmp(cmd, "echo") == 0)
		return (1);
	else if (strcmp(cmd, "cd") == 0)
		return (1);
	else if (strcmp(cmd, "pwd") == 0)
		return (1);
	else if (strcmp(cmd, "export") == 0)
		return (1);
	else if (strcmp(cmd, "unset") == 0)
		return (1);
	else if (strcmp(cmd, "env") == 0)
		return (1);
	else if (strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}
