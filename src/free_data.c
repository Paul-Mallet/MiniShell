/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:56:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 14:06:26 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"
#include "../includes/executing.h"
#include "../includes/signals.h"
		
void	free_data(t_data *data)
{
	if (data->env)
		free_env(&data->env);
	free_processing(data);
}

void	free_processing(t_data *data)
{
	if (data->tokens)
		free_tokens(&data->tokens);
	if (data->cmds)
		free_cmd_struct(&data->cmds);
	if (data->prompt)
		free(data->prompt);
	if (data->input)
		free(data->input);
	if (data->pids)
		free(data->pids);
	if (data->char_env)
		free_strs(data->char_env);
}
