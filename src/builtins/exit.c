/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:10 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/13 15:17:03 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void	ft_exit(t_env *env, t_alias *alias)
{
	if (env)
		free_env(env);
	if (alias)
		free_alias(alias);
	exit(0);
}
