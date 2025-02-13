/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:46:29 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/13 14:26:40 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

/*
	builtins conditions
	1. input is already parsed(trim, cmds, args validation)
	2. check input fit builtins names(strcmp)
	3. send input without builtins(strchr + 1, skip ' ')
*/
void	ft_builtins(char *input, t_env *env)
{
	// if (!ft_strcmp(input, "echo"))
		// ft_echo();
	if (!ft_strncmp(input, "cd", 2))
		ft_cd(ft_strchr(input, ' ') + 1);
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
