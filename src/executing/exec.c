/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:26:39 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/26 18:56:55 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"

void	exec(t_data *data)
{
	int	nb_cmd;

	nb_cmd = count_cmd(data->cmds);
	if (nb_cmd > 1)
		exec_multiple_cmds(data, nb_cmd);
	exec_simple_cmd(data);
	ft_builtins(data);
	
}

void	exec_multiple_cmds(t_data *data, int nb_cmd)
{
	while (nb_cmd)
}

void	exec_multiple_cmd(t_data *data)
{
	
}

int	exec_command(t_data *data)
{
	pid_t	pid;

	pid = fork();
}