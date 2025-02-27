/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenizer_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:02 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/27 16:05:45 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int is_executable(char *path)
{
    struct stat file_infos;

    if (stat(path, &file_infos) != 0)    // Vérifie si le fichier existe
        return (127); // Commande non trouvée
    if (!S_ISREG(file_infos.st_mode))     // Vérifie si c'est un fichier régulier
        return (126); // Trouvé mais non exécutable
    if (access(path, X_OK) != 0)    // Vérifie si l'utilisateur a les permissions d'exécution
        return (126); // Permission denied
    return (0); // Commande valide et exécutable
}

int is_cmd(char **paths, char *cmd)
{
    int	i;
	int	status;
    char *road;

	if (!cmd)
		return (127);
    if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
        return (is_executable(cmd)); // Si la commande est un chemin absolu ou relatif, verifier directement
    if (!paths)		// Si $PATH est NULL, Bash ne cherche pas plus loin
        return (127); 		// Commande non trouvee
    i = 0;
    while (paths[i]) // Recherche dans chaque dossier du PATH
    {
        road = construct_path(paths[i], cmd);
        if (!road)
            return (2); // Erreur mémoire
        status = is_executable(road);
        free(road);
        if (status == 0 || status == 126) // Trouve mais non executable ou trouve et executable
            return (status);
        i++;
    }
    return (127); // Commande non trouvée
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
