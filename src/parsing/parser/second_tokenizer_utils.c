/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenizer_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:02 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/13 13:21:17 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int	is_executable(char *cmd, t_data *data)
{
	if (access(cmd, F_OK) != 0)
	{
		perror("access");
		data->exit_code = 127;
		return (0);
	}
	if (is_dir(cmd))
	{
		printf("%s is a directory\n", cmd);
		data->exit_code = 126;
		return (0);
	}
	if (access(cmd, X_OK) != 0)
	{
		printf("No premissions\n");
		data->exit_code = 126;
		return (0);
	}
	return (1);
}

int	is_cmd(char **paths, char *cmd, t_data *data)
{
	int		i;
	char	*road;

	if (!paths)
	{
		if (is_executable(cmd, data))
			return (1);
		return (0);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (is_executable(cmd, data))
			return (1);
		return (0);
	}
	i = 0;
	while (paths[i])
	{
		road = construct_path(paths[i], cmd);
		if (access(road, F_OK) == 0)
		{
			is_executable(road, data);
			free(road);
			return (1);
		}
		free(road);
		i++;
	}
	data->code = 127;
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
