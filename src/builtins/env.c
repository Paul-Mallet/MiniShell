/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:41:49 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 04:09:39 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		ft_printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}	
}

void	ft_env(t_data *data)
{
	data->exit_code = 0;
	print_env(data->env);
}
