/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:41:49 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/10 12:12:29 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void	print_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}	
}

void	ft_env(t_env *env)
{
	print_env(env);
}
