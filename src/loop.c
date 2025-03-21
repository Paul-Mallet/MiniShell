/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:59:59 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/21 19:30:57 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"
#include "executing.h"
#include "signals.h"

void	init_data(t_data *data)
{
	data->env = NULL;
	data->cmds = NULL;
	data->pids = NULL;
	data->tokens = NULL;
	data->prompt = NULL;
	data->char_env = NULL;
	data->exit_code = 0;
}

void	ctrl_d_exit(t_data *data)
{
	ft_exit(data, NULL);
}

// "" -> must be cmd not found
void	loop_minishell(t_data *data, char **envp)
{
	data->input = NULL;
	data->env = import_env(envp);
	if (!data->env)
		return ;
	while (1)
	{
		data->input = readline("$");
		if (g_exit_code == 130)
		{
			data->exit_code = g_exit_code;
			g_exit_code = 0;
		}
		if (data->input == NULL)
			ctrl_d_exit(data);
		if (!ft_lexer(data))
			continue ;
		add_history(data->input);
		if (!ft_parsing(data->input, data))
			continue ;
		if (!init_cmd_struct(data))
			continue ;
		exec(data);
		free_processing(data);
	}
	free_data(data);
}
