/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:56:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/12 14:34:26 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"
#include "../includes/executing.h"
#include "../includes/signals.h"

void	free_exec(t_data *data)
{
	t_cmd	*current;

	print_cmd_struct(data->cmds);
	current = data->cmds;
	while(current)
	{
		if (current->fd[0] != -1)
			close(data->cmds->fd[0]);
		if (current->fd[1] != -1)
			close(data->cmds->fd[1]);
		current = current->next;
	}
	free_strs(data->char_env);
}
