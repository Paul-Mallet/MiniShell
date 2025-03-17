/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:17:37 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 11:52:24 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"
#include "../../../includes/executing.h"

char	**malloc_cmd(t_token *tokens)
{
	t_token	*current;
	char	**cmd;
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
	cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	**build_cmd(t_token	*tokens, char **cmd)
{
	t_token	*current;
	int		i;

	i = 0;
	current = tokens;
	while (current)
	{
		if (current->subtype == ARG)
			cmd[i++] = ft_strdup(current->value);
		if (current->type == PIPE)
			break ;
		current = current->next;
	}
	cmd[i] = NULL;
	return (cmd);
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
	char	**cmd;
	t_cmd	*head;
	t_cmd	*new;
	t_token	*current;
	char	**prompt_cmd;

	cmd = NULL;
	head = NULL;
	new = NULL;
	current = data->tokens;
	while(current)
	{
		cmd = malloc_cmd(current);
		if (!cmd)
			return (NULL);
		prompt_cmd = build_cmd(current, cmd);
		new = new_cmd(prompt_cmd);
		cmd_struct_add_back(&head, new);
		init_redirs(current, new);
		current = to_pipe_or_last_token(current);
		current = current->next;
	}
	if (!head)
		return (free_processing(data), false);
	data->cmds = head;
	init_id_cmds(data->cmds);
	return (true);
}
