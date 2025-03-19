/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:26:39 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 10:34:48 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"
#include "signals.h"

void	exec(t_data *data)
{
	int		nb_cmd;

	data->char_env = make_env(data->env);
	check_heredoc(data);
	nb_cmd = count_cmds(data->cmds);
	printf("nb_cmd: %d\n", nb_cmd);
	if (nb_cmd == 1)
		exec_simple_cmd(data);
	else
		exec_multiple_cmds(data, nb_cmd);
}
