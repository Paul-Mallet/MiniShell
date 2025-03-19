/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:41:57 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 04:15:06 by abarahho         ###   ########.fr       */
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
}
void	unset_env_var(t_data *data, char *key)
{
	t_env	*current;
	t_env	*prev;

	// current = *env;
	current = data->env;
	prev = NULL;
	data->exit_code = 0;
	while (current)
	{ 
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				data->env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
