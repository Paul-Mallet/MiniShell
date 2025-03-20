/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:56:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/20 17:22:45 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"
#include "executing.h"
#include "signals.h"

void	free_strs(char **paths)
{
	int		i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	paths = NULL;
}

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
	free_parsing(data);
	if (data->cmds)
		close_pipes(data->cmds);
	if (data->env)
		free_env(&data->env);
	if (data->cmds)
		free_cmd_struct(&data->cmds);
}

void	free_data(t_data *data)
{
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
	// if (data->char_env)
		// free_strs(data->char_env);
}

void	free_simple_cmd(t_data *data)
{
	free_strs(data->char_env);
	if (data->cmds)
		close_pipes(data->cmds);
	if (data->env)
		free_env(&data->env);
	free_processing(data);
}
