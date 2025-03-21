/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:34:21 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/21 16:34:37 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"

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
	new->fd[0] = -1;
	new->fd[1] = -1;
	new->id = 0;
	new->has_input = false;
	new->has_output = false;
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

void	free_cmd_struct(t_cmd **cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmds || !*cmds)
		return ;
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
