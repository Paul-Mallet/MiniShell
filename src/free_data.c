/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:56:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/13 19:05:24 by abarahho         ###   ########.fr       */
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
	if (data->char_env)
		free_strs(data->char_env);
}
		
void	free_data_children(t_data *data)
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

bool	check_tokens(t_data *data)
{
	if (!data->tokens->next && data->tokens->subtype != CMD)
	{
		error_handling(SYNTAX_ERROR_NEAR_TOKEN, data->tokens->value);
		data->exit_code = 2;
		free_data(data);
		return (false);
	}
	return (true);
}