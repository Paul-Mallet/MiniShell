/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:59:59 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/14 17:03:55 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"

static char	*get_prompt()
{
	char	*prompt;
	char	name[BUFFER_SIZE];

	getcwd (name, BUFFER_SIZE); //errors
	prompt = ft_strjoin(name, "$ "); //errors
	return (prompt);
}

void	init_mini_shell(t_env *env)
{
	char 	*input;
	char	*prompt;

	prompt = get_prompt();
	while ((input = readline(prompt)))
	{
		if (input)
			add_history(input);
		//if (!ft_lexer(input))
			//free + exit();
		input = ft_parsing(input);
		ft_builtins(input, env);
		prompt = get_prompt();
		free(input);
	}
}
