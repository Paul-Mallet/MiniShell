/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:18 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/12 16:53:15 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

int main(int ac, char **av, char **envp)
{
	char *input;
	(void)ac;
	(void)av;
	t_env   *env;

	env = import_env(envp);
	while ((input = readline("MiniShell$>")))
	{
		if (input)
			add_history(input);
		if (!ft_strcmp(input, "export"))
			ft_export(input, &env);
		if (!ft_strcmp(input, "exit"))
			ft_exit(env);
		if (!ft_strcmp(input, "unset"))
			ft_unset(&env, input);
		if (!ft_strcmp(input, "env"))
			ft_env(env);
		free(input);
	}
	return (0);
}