/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:46:29 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/13 14:58:47 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void	ft_builtins(char *input, t_env *env, t_alias *alias)
{
	if (!ft_strcmp(input, "echo"))
		ft_echo(input, alias, true);
	// if (!ft_strcmp(input, "cd"))
		// ft_cd();
	if (!ft_strcmp(input, "pwd"))
		ft_pwd();
	if (!ft_strcmp(input, "export"))
		ft_export(input, &env);
	// if (!ft_strcmp(input, "unset"))
		// ft_unset(&env, key);
	if (!ft_strcmp(input, "env"))
		ft_env(env);
	// if (!ft_strcmp(input, "exit"))
	// 	ft_exit(env, alias);
}
