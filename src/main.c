/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:18 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/20 14:01:17 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"

int main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	//if (isatty(STDIN_FILENO))
	// {
	init_data(&data);
	init_mini_shell(&data, envp);
	// }
	return (0);
}
