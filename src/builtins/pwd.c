/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:39:46 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/24 16:18:35 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	ft_pwd(t_data *data)
{
	char	path[BUFFER_SIZE];

	if (!getcwd(path, BUFFER_SIZE))
	{
		perror("minishell: pwd");
		data->exit_code = 2;
		return ;
	}
	printf("%s\n", path);
	data->exit_code = 0;
}
