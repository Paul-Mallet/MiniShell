/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:18 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/12 14:01:19 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

int main(int ac, char **av, char **envp)
{
	t_env   *our_env;

	(void)ac;
	(void)av;
	our_env = import_env(envp);
	print_env(our_env);
	unset_env(&our_env, "COLORTERM");
	print_env(our_env);
	free_env(our_env);
	return (0);
}