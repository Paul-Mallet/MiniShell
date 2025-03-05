/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:59:59 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/05 17:28:59 by abarahho         ###   ########.fr       */
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
void	check_ctrl_d(t_data *data, char *input)
{
	if (!input)
	{
		printf("exit\n");
		free_env(&data->env); //?
		exit(EXIT_FAILURE);
	}
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
		printf("\n\n\n%s\n\n\n\n", input);
		if (!input)
		{
			printf("\n\n\ninput: %s\n\n\n\n", input);
			printf("\nerror input\n");
			free(prompt);
			break ; //continue?
		}
		check_ctrl_d(data, input);
		add_history(input);
		ft_lexer(input);
		ft_parsing(input, data);
		data->cmds = init_cmd_struct(data->tokens);
		ft_builtins(data);
		// check_tokens(data->tokens);
		// print_token(data->tokens);
		// if (data->cmds->cmd)
		exec(data);
		free_tokens(&data->tokens);
		// free(input);
		free(prompt);
	}
}
