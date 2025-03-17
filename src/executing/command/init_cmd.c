/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:17:37 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 18:37:09 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executing.h"

static unsigned int	cmds_len(t_token *tokens)
{
	t_token	*curr;
	int		i;

	i = 0;
	curr = tokens;
	while (curr)									//while in sub-function
	{
		if (curr->subtype == ARG)
			i++;
		if (curr->type == PIPE)
			break ;
		curr = curr->next;
	}
	return (i);
}

static char	**build_cmds(t_token *tokens)	//cmds, malloc inside
{
	t_token	*curr;
	char	**cmds;
	int		i;

	cmds = (char **)malloc(sizeof(char *) * (cmds_len(tokens) + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	curr = tokens;
	while (curr)
	{
		if (curr->subtype == ARG)
			cmds[i++] = ft_strdup(curr->value);
		if (curr->type == PIPE)
			break ;
		curr = curr->next;
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

void	free_prompt(char **prompt_cmd)
{
	int	i;

	i = -1;
	while (prompt_cmd[++i])
		free(prompt_cmd[i]);
	free(prompt_cmd);
}

void	print_cmd(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		printf("cmd[%d]: %s\n", i, cmds[i]);
}

bool	init_cmd_struct(t_data *data)
{
	t_cmd	*head;
	t_cmd	*new;
	t_token	*curr;

	head = NULL;
	new = NULL;
	curr = data->tokens;
	while(curr)
	{
		new = new_cmd(build_cmds(curr));
		cmd_struct_add_back(&head, new);
		init_redirs(curr, new);
		curr = to_pipe_or_last_token(curr);
		curr = curr->next;
	}
	if (!head)
		return (free_processing(data), false);
	data->cmds = head;
	init_id_cmds(data->cmds);
	return (true);
}
