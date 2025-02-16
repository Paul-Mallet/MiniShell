/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:55:18 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/16 18:52:53 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"

int main(int ac, char **av, char **envp)
{
	t_env	*env;
	char	*str;
	t_data	*data;
	(void)ac;

	init_data(data)
	env = import_env(envp);
	str = expander(av[1], env);
	print_export(env);
	printf("%s", str);
	free_env(&env);
    ft_exit(data);
}
