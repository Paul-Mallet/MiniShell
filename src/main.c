/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:18 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/06 16:42:27 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"
#include "../includes/signals.h"

int main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	signals_handler();
	init_data(&data);
	init_mini_shell(&data, envp);
	return (0);
}
