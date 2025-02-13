/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:17:29 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/13 15:19:36 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

t_alias	*create_alias(char *name, char *value)
{
	t_alias *new;

	new = (t_alias *)malloc(sizeof(t_alias));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	add_alias(t_alias **list, t_alias *new)
{
	if (!new || !list)
		return ;
	new->next = *list;
	*list = new;
}

void	free_alias(t_alias *alias)
{
	t_alias *tmp;

	while (alias)
	{
		tmp = alias->next;
		free(alias->name);
		free(alias->value);
		free(alias);
		alias = tmp;
	}
}
