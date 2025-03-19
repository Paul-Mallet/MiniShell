/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:56:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 07:27:15 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"
#include "executing.h"
#include "signals.h"

void free_pids(t_data *data)
{
    if (data->pids)
    {
        free(data->pids);
        data->pids = NULL;
    }
}

void	free_exit(t_data *data)
{
	if (data->cmds)
		close_pipes(data->cmds);
	if (data->env)
		free_env(&data->env);
	free_parsing(data);
	if (data->cmds)
		free_cmd_struct(&data->cmds);
}

void	free_data(t_data *data)
{
	free_pids(data);
	if (data->cmds)
		close_pipes(data->cmds);
	if (data->env)
		free_env(&data->env);
	free_processing(data);
}

void	free_parsing(t_data *data)
{
	if (data->tokens)
		free_tokens(&data->tokens);
	if (data->prompt)
		free(data->prompt);
	if (data->input)
		free(data->input);
}

void	free_processing(t_data *data)
{
	free_parsing(data);
	if (data->cmds)
		free_cmd_struct(&data->cmds);
	if (data->char_env)
		free_strs(data->char_env);
}
