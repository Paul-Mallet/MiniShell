/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenizer_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:02 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 19:21:04 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

// int ft_is_all_alnum(char *str)
// {
// 	while (*str)
// 	{
// 		if (!ft_isalnum(*str))
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }

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

bool	is_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}
