/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:39:46 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/22 14:16:24 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	ft_pwd(t_data *data, t_cmd *cmds)
{
	char	path[BUFFER_SIZE];

	if (ft_strcmp(cmds->cmd[0], "pwd") == 0 && cmds->cmd[1])
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
