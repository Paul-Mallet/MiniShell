/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:41:57 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 20:39:03 by pamallet         ###   ########.fr       */
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
	t_env	*curr;
	t_env	*prev;

	curr = data->env;
	prev = NULL;
	while (curr)
	{ 
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				curr = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
