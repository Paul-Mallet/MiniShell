/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:26:39 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/20 12:24:19 by paul_mallet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"
#include "signals.h"

/*
	to fix:
	* cat | | cat
*/
void	exec(t_data *data)
{
	int		nb_cmd;

	check_heredoc(data);
	nb_cmd = count_cmds(data->cmds);
	if (nb_cmd == 1)
		exec_simple_cmd(data);
	else
		exec_multiple_cmds(data, nb_cmd);
}
