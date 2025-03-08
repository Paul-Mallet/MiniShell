/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:59:59 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/07 19:31:08 by abarahho         ###   ########.fr       */
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
	printf("exit\n");
	if (prompt)
		free(prompt);
	if (data->cmds->cmd)
		free_strs(data->cmds->cmd);
	free_env(&data->env);
	exit(EXIT_FAILURE);
}

void	init_mini_shell(t_data *data, char **envp)
{
	char 	*input;
	char	*prompt;

	input = NULL;
	data->env = import_env(envp);
	while (1)
	{
		prompt = get_prompt();
		if (!prompt){
			printf("\nerror input\n");
			break ;
		}
		input = readline(prompt);
		if (!input)
			ctrl_d_exit(data, prompt);
		add_history(input);
		ft_lexer(input);
		ft_parsing(input, data);
		data->cmds = init_cmd_struct(data->tokens);
		print_token(data->tokens);
		print_cmd_struct(data->cmds);
		exec(data);
		free_tokens(&data->tokens);
		free(prompt);
	}
}
