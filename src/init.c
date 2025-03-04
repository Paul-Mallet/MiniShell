/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:59:59 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/04 17:40:31 by abarahho         ###   ########.fr       */
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

void	init_mini_shell(t_data *data, char **envp)
{
	char 	*input;
	char	*prompt;
	int i = 0;

	data->env = import_env(envp);
	prompt = get_prompt();
	if (!prompt)
		return;
	while ((input = readline(prompt)))
	{
		printf("%d\n", i);
		i++;
		if (input)
			add_history(input);
		ft_lexer(input);
		ft_parsing(input, data);
		data->cmds = init_cmd_struct(data->tokens);
		ft_builtins(data);
		free(prompt);
		prompt = get_prompt();
		if (!prompt)
			break ;
		// check_tokens(data->tokens);
		print_token(data->tokens);
		exec(data);
		printf("after exec\n");
		free_tokens(&data->tokens);
		free(input);
	}
}
