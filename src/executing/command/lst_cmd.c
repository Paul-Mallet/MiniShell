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

#include "../../../includes/minishell.h"
#include "../../../includes/executing.h"

t_cmd	*new_cmd(char **cmds)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = cmds;
	new->redir = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	cmd_struct_add_back(t_cmd **cmds, t_cmd *new)
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

void free_cmd_struct(t_cmd **cmds)
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
		if (current->redir)
			free_redir(&current->redir);
        free(current);
        current = next;
    }
    *cmds = NULL;
}
