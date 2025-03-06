/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenizer_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:02 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/06 13:38:14 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int is_executable(char *cmd)
{
    if (access(cmd, F_OK) != 0)
	{
		// printf("acces F_OK\n");
        perror("access");
        return (0);
    }
	if (is_dir(cmd))
	{
		// printf("is_dir\n");
		printf("%s is a directory\n", cmd);
		return (0);
	}
    if (access(cmd, X_OK) != 0)
	{
		// printf("acces X_OK\n");
        printf("No premissions\n");
        return (0);
    }
    return (1);
}

int is_cmd(char **paths, char *cmd)
{
    int		i;
    char	*road;

    if (!paths)		// Si $PATH est NULL, Bash ne cherche pas plus loin
	{
		// printf("no PATH\n");
		if (is_executable(cmd))
			return (1);
		return (0);
	}
	if (ft_strchr(cmd, '/'))
	{
		// printf("there is '/'\n");
		if (is_executable(cmd))
			return (1);
		return (0);
	}
    i = 0;
    while (paths[i]) // Recherche dans chaque dossier du PATH
    {
        road = construct_path(paths[i], cmd);
		if (access(road, F_OK) == 0)
		{
			is_executable(road);
			return (1);
		}
        free(road);
        i++;
    }
	// printf("command not found\n");
    return (0); // Commande non trouvée
}


int	is_file(char *value)
{
	struct	stat	file_infos;

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
