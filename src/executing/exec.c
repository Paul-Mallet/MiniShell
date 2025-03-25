/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:26:39 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/25 10:42:10 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"
#include "signals.h"

void	exec(t_data *data)
{
	int		nb_cmd;

	if (check_heredoc(data) != 0)
		return ;
	nb_cmd = count_cmds(data->cmds);
	if (nb_cmd == 1)
		exec_simple_cmd(data);
	else
		exec_multiple_cmds(data, nb_cmd);
}
