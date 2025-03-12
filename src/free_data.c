/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:56:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/12 16:59:54 by abarahho         ###   ########.fr       */
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
		
void	free_data(t_data *data)
{
	if (data)
		free_exec(data);
	if (data->env)
		free_env(&data->env);
	if (data->tokens)
		free_tokens(&data->tokens);
	if (data->cmds)
		free_cmd_struct(&data->cmds);
	if (data->prompt)
		free(data->prompt);
	if (data->input)
		free(data->input);
}