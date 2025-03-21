/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:56:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/21 19:29:47 by abarahho         ###   ########.fr       */
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
}

void	free_pids(t_data *data)
{
	free(data->pids);
	free_data(data);
}

void	free_data(t_data *data)
{
	if (data->cmds)
		close_pipes(data->cmds);
	if (data->env)
		free_env(&data->env);
	if (data->tokens)
		free_tokens(&data->tokens);
	if (data->prompt)
		free(data->prompt);
	if (data->input)
		free(data->input);
	if (data->cmds)
		free_cmd_struct(&data->cmds);
	if (data->char_env)
		free_strs(data->char_env);
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
	if (data->tokens)
		free_tokens(&data->tokens);
	if (data->prompt)
		free(data->prompt);
	// if (data->input)
	// 	free(data->input);
	if (data->cmds)
		free_cmd_struct(&data->cmds);
}
