/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:46:29 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/12 18:09:34 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void	ft_builtins(char *input, t_env *env)
{
	// if (!ft_strcmp(input, "echo"))
		// ft_echo();
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
	if (!ft_strcmp(input, "exit"))
		ft_exit(env);
}
