/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:18 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/12 15:00:11 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

// int main(int ac, char **av, char **envp)
// {
// 	t_env   *our_env;

// 	(void)ac;
// 	(void)av;
// 	our_env = import_env(envp);
// 	print_env(our_env);
// 	unset_env(&our_env, "COLORTERM");
// 	print_env(our_env);
// 	free_env(our_env);
// 	return (0);
// }

int main(int ac, char **av, char **envp)
{
	char *input;
	(void)ac;
	(void)av;
	t_env   *env;

	env = import_env(envp);
	while ((input = readline("MiniShell$>")))
	{
		if (input) add_history(input);
			printf("Vous avez tapé: %s\n", input);
		free(input);
		if (!ft_strcmp(input, "exit"))
			ft_exit(env);
	}
	return (0);
}