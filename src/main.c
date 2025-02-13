/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:18 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/13 15:52:49 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

char	*get_prompt()
{
	char	*prompt;
	char	name[BUFFER_SIZE];

	getcwd(name, BUFFER_SIZE); //errors
	prompt = ft_strjoin(name, "$ "); //errors
	return (prompt);
}

void	launch_mini_shell(t_env *env)
{
	char 	*input;
	char	*prompt;

	prompt = get_prompt();
	while ((input = readline(prompt)))
	{
		if (input) add_history(input);
		// 	ft_printf("Vous avez tapé: %s\n", input);
		ft_builtins(input, env);
		prompt = get_prompt();
		free(input);
	}
}

int main(int ac, char **av, char **envp)
{
	t_env   *env;

	(void)ac;
	(void)av;
	env = import_env(envp);
	launch_mini_shell(env);
	return (0);
}
