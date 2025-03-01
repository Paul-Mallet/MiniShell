/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenizer_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:02 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/28 19:35:19 by paul_mallet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

// int is_executable(char *cmd)
// {
// 	struct	stat file_infos;
// 	int		permissions;

//     if (access(cmd, F_OK) == -1)
// 	{
//         perror("access");
//         return (0);
//     }
//     if (stat(cmd, &file_infos) == -1)
// 	{
//         perror("stat");
//         return 0;
//     }
//     if (S_ISDIR(file_infos.st_mode) == -1)
// 	{
// 		perror("stat");
//         return 0;
//     }
//     if (access(cmd, F_OK) == -1)
// 	{
//         printf("Le fichier n'a pas la permission d'exécution.\n");
//         return 0;
//     }

//     return 1;
// }

// int is_cmd(char **paths, char *cmd)
// {
//     int	i;
// 	int	status;
//     char *road;


//     if (!paths)		// Si $PATH est NULL, Bash ne cherche pas plus loin
// 	{
// 		if (!is_executable(cmd));
// 			return (1);
// 		return (0);
// 	}
// 	if (ft_strchr(cmd, '/'))
// 	{
// 		if (!is_executable(cmd));
// 			return (1);
// 		return (0);
// 	}
//     i = 0;
//     while (paths[i]) // Recherche dans chaque dossier du PATH
//     {
//         road = construct_path(paths[i], cmd);
//         if (!road)
//             return (1);
//         status = is_executable(road);
//         free(road);
//         if (status == 0 || status == 126) // Trouve mais non executable ou trouve et executable
//             return (status);
//         i++;
//     }
//     return (127); // Commande non trouvée
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
