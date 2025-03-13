/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:59:59 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/13 19:00:22 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"
#include "../includes/executing.h"
#include "../includes/signals.h"

void	init_data(t_data *data)
{
	data->env = NULL;
	data->cmds = NULL;
	data->pids = NULL; //g_exit_code
	data->tokens = NULL;
	data->prompt = NULL;
	data->char_env = NULL;
	data->exit_code = 0;
}

static char	*get_prompt(void)
{
	char	*prompt;
	char	name[BUFFER_SIZE];

	if (!getcwd(name, BUFFER_SIZE))
	{
		perror("getcwd error");
		return (NULL);
	}
	prompt = ft_strjoin(name, "$ ");
	return (prompt);
}

/*
	check Ctrl + D EOF
	* 
*/
void	ctrl_d_exit(t_data *data, char *prompt)
{
	if (prompt)
		free(prompt);
	if (data->env)
		free_env(&data->env);
	if (data->cmds)
		free_cmd_struct(&data->cmds);
	if (data->tokens)
		free_tokens(&data->tokens);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

void	init_mini_shell(t_data *data, char **envp)
{
	data->input = NULL;
	data->env = import_env(envp);
	if (!data->env)
		return ;
	while (1)
	{
		data->prompt = get_prompt();
		data->input = readline(data->prompt);
		if (data->input == NULL)
			ctrl_d_exit(data, data->prompt);
		add_history(data->input);
		if (!ft_lexer(data))
			continue ;
		ft_parsing(data->input, data);
		if (!check_tokens(data))
			continue ;
		data->cmds = init_cmd_struct(data->tokens);
		print_cmd_struct(data->cmds);
		exec(data);
		if (g_exit_code)
			g_exit_code = 0;
		free_data(data);
		data->input = NULL;
	}
}

void	free_data(t_data *data)
{
	if (data->cmds)
	{
		free_exec(data);
		free_cmd_struct(&data->cmds);
	}
	if (data->tokens)
		free_tokens(&data->tokens);
	if (data->prompt)
		free(data->prompt);
	if (data->input)
		free(data->input);
}