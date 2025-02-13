/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:18 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/13 10:55:25 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

int main(int ac, char **av, char **envp)
{
	char *input;
	t_env   *env;

	(void)ac;
	(void)av;
	env = import_env(envp);
	while ((input = readline("MiniShell$>")))
	{
		if (input) add_history(input);
			ft_printf("Vous avez tapé: %s\n", input);
		ft_builtins(input, env);
		free(input);
	}
	return (0);
