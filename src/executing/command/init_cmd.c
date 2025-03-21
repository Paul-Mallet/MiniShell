/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:17:37 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/21 19:17:16 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executing.h"

static unsigned int	cmds_len(t_token *tokens)
{
	t_token	*current;
	int		i;

	i = 0;
	current = tokens;
	while (current)
	{
		if (current->subtype == ARG)
			i++;
		if (current->type == PIPE)
			break ;
		current = current->next;
	}
	return (i);
}

static char	**build_cmds(t_token *tokens)	//cmds, malloc inside
{
	t_token	*current;
	char	**cmds;
	int		i;

	cmds = (char **)malloc(sizeof(char *) * (cmds_len(tokens) + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	current = tokens;
	while (current)
	{
		if (current->subtype == ARG)
			cmds[i++] = ft_strdup(current->value);
		if (current->type == PIPE)
			break ;
		current = current->next;
	}
	cmds[i] = NULL;
	return (cmds);
}

t_token	*to_pipe_or_last_token(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current->next)
	{
		if (current->type == PIPE)
			break ;
		current = current->next;
	}
	return (current);
}

bool	init_cmd_struct(t_data *data)
{
	t_cmd	*head;
	t_cmd	*new;
	t_token	*current;

	head = NULL;
	new = NULL;
	current = data->tokens;
	while (current)
	{
		new = new_cmd(build_cmds(current));
		cmd_struct_add_back(&head, new);
		init_redirs(current, new);
		current = to_pipe_or_last_token(current);
		current = current->next;
	}
	// if (!head)
	// 	return (free_processing(data), false);
	data->cmds = head;
	init_id_cmds(data->cmds);
	return (true);
}
