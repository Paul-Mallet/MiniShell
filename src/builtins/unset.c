/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:41:57 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/25 13:15:33 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	ft_unset(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
		unset_env_var(data, cmd[i]);
	data->exit_code = 0;
}

void	unset_env_var(t_data *data, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (data->env)
		current = data->env;
	else
		return ;
	prev = NULL;
	while (current)
	{


		{
			if (prev)
				prev->next = current->next;
			else
				current = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
