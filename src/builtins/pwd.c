/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:39:46 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 03:43:18 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

//malloc path, if < path, realloc with bigger size
void	ft_pwd(t_data *data)
{
	char	path[BUFFER_SIZE];

	if (!getcwd(path, BUFFER_SIZE))
	{
		perror("pwd");
		data->exit_code = 2;
		exit(1);
	}
	ft_printf("%s\n", path);
	data->exit_code = 0;
}
