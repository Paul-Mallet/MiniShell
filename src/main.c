/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:18 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/17 19:36:49 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"
#include "signals.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	
	//handle_interactive_mode();
	//gerer exit_code
	signals_handler();
	init_data(&data);
	loop_minishell(&data, envp);
	return (0);
}
