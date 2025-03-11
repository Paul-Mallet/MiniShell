/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:56:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/11 11:59:19 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"
#include "../includes/executing.h"
#include "../includes/signals.h"

void	free_exec(t_data *data)
{
	while(data->cmds)
	{
		if (data->cmds->fd[0] != -1)
			close(data->cmds->fd[0]);
		if (data->cmds->fd[1] != -1)
			close(data->cmds->fd[1]);
		data->cmds = data->cmds->next;
	}
	free_strs(data->char_env);
}
