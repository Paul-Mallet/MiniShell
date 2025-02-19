/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenizer_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:02 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/19 14:36:07 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

bool	is_cmd(char **paths, char *cmd)
{
	int		i;
	char	*road;

	if (!paths || !cmd)
		return (false);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (true);
	i = 0;
	while (paths[i])
	{
		road = construct_path(paths[i], cmd);
		if (road && access(road, F_OK) == 0)
		{
			free(road);
			return (true);
		}
		free(road);
		i++;
	}
	return (false);
}

// int	is_absolute_path(char *path)
// {
// 	return (path && (path[0] == '/' || (path[0] == '.' && path[1] == '/')));
// }

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
