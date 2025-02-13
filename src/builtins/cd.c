/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:39:36 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/13 14:39:28 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

/*
	cd cases
	* absolute path: cd "/usr/local/bin"
		* if start "/" ...
	* relative path: cd "document/test"
		* change to ./document/test
	* chdir("both paths")
		* return (0) or (-1);
	* perror()
		* if chdir() return (-1);
		* 3 cases: No such file or directory, Not a dir, permission denied
*/
void	ft_cd(char *path)
{
	char	s[BUFFER_SIZE];

	if (chdir(path) == -1)
		perror("cd"); //bash: cd: error_msg
}