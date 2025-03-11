/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:59:59 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/11 11:53:08 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"
#include "../includes/executing.h"
#include "../includes/signals.h"

void	init_data(t_data *data)
{
	data->cmds = NULL;
	data->env = NULL;
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
	char	*input;

	input = NULL;
	data->env = import_env(envp);
	while (1)
	{
		data->prompt = get_prompt();
		input = readline(data->prompt);
		if (!input)
			ctrl_d_exit(data, data->prompt);
		add_history(input);
		ft_lexer(input);
		ft_parsing(input, data);
		data->cmds = init_cmd_struct(data->tokens);
		print_token(data->tokens);
		if (exec(data))
			data->exit_code = EXIT_FAILURE;
		free_exec(data);
		free_tokens(&data->tokens);
		free_cmd_struct(&data->cmds);
		free(data->prompt);
		free(input);
		input = NULL;
	}
}
