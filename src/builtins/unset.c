/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:41:57 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/24 17:30:37 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void	ft_unset(t_env **env, t_token *tokens)
{
	t_token	*current;

	current = tokens->next;
	while (current)
	{
		if (tokens->next && tokens->subtype == IS_SEPARATOR)
			current = current->next;
		else if (tokens->type == WORD)
		{
			unset_env_var(env, current->value);
			current = current->next;
		}
		else
			return ;
	}
}
void	unset_env_var(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}