/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:39:46 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 20:08:24 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	ft_pwd(t_data *data)
{
	char	path[BUFFER_SIZE];

	if (data->cmds->cmd[1])
	{
		printf("minishell: pwd: options not allowed\n");
		data->exit_code = 2;
		return ;
	}
	if (!getcwd(path, BUFFER_SIZE))
	{
		perror("minishell: pwd");
		data->exit_code = 2;
		return ;
	}
	printf("%s\n", path);
	data->exit_code = 0;
}
