/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:44:07 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/23 14:07:41 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"

t_cmd	*new_cmd(t_cmd tokens)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->redirs = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	cmd_add_back(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*current;

	if (!cmds || !new)
		return ;
	if (!*cmds)
	{
		*cmds = new;
		return ;
	}
	current = *cmds;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
}

void free_cmd(t_cmd **cmds)
{
    t_cmd *current;
    t_cmd *next;

    if (!cmds || !*cmds)
        return;
    current = *cmds;
    while (current)
    {
        next = current->next;
        free_strs(current->cmd);
		free_redir(current->redirs);
        free(current);
        current = next;
    }
    *cmds = NULL;
}
