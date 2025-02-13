/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:39:46 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/13 15:19:56 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void	ft_pwd(void)
{
	char	path[BUFFER_SIZE];

	if (!getcwd(path, BUFFER_SIZE))
	{
		perror("pwd");
		exit(1);
	}
	ft_printf("%s\n", path);
}
