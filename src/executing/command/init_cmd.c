/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:17:37 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/25 19:34:28 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"
#include "../../../includes/executing.h"

char	**malloc_cmd(t_token *tokens)
{
	char	**cmd;
	int		size;

	size = 0;
	while (tokens)
	{		
		if (tokens->subtype == CMD || tokens->subtype == ARG)
			size++;
		if (tokens->type == PIPE || tokens->subtype == DELIM)
			break ;
		tokens = tokens->next;
	}
	cmd = (char **)malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	**build_cmd(t_token	*tokens, char **cmd) //["value1", "value2"]
{
	int		i;
	bool	cmd_found;

	i = 0;
	cmd_found = false;
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			if (tokens->subtype == CMD && cmd_found == false)
			{
				cmd[i++] = ft_strdup(tokens->value);
				cmd_found = true;
			}
			else if (tokens->subtype == ARG && cmd_found == true)
				cmd[i++] = ft_strdup(tokens->value);
		}
		if (tokens->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_token	*to_pipe_token(t_token *tokens)
{
	while (tokens->next) //not check last token == PIPE
	{
		if (tokens->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	tokens = tokens->next;
	return (tokens);
}

void	fill_redir(t_token *tokens, t_redir *new)
{
	printf("SUBTYPE: %u\n", tokens->subtype);
	new->file = NULL;
	new->value = NULL;
	new->value = tokens->value;
	new->fd = -1;
    new->append = false;
    new->heredoc = false;
	new->delimiter = NULL;
	if (tokens->next && tokens->next->subtype == FILES)
		new->file = tokens->next->value;
	else if (tokens->next->next && tokens->next->next->subtype == FILES)
		new->file = tokens->next->next->value;
	if (tokens->subtype == APPEND)
		new->append = true;
	else if (tokens->subtype == HEREDOC)
	{
		new->heredoc = true;
		if (tokens->next && tokens->next->subtype == DELIM)
			new->delimiter = tokens->next->value;
		else if (tokens->next->next && tokens->next->next->subtype == DELIM)
			new->delimiter = tokens->next->next->value;
	}
}

void	init_redir(t_token *tokens, t_cmd *new)
{
	t_token	*current;
	t_redir	*redir;

	tokens = to_pipe_token(tokens); //will not fill_redir if grep test<END>
	if (!tokens)
		return ;
	current = tokens; //tokens->type = PIPE
	redir = NULL;
	while (current->prev) //handle 1rst token == redir
	{
		printf("SUBTYPE: %u\nPREV_VALUE: %s\n", current->subtype, current->prev->value);
		if (current->type == REDIR)
		{
			redir = malloc(sizeof(t_redir));
			if (!redir)
				printf("failed");
			fill_redir(current, redir);
			break ;
		}
		current = current->prev;
	}
	new->redir = redir;
	// printf("failed");
}

/*
	init_cmds_struct
	1. build_cmd -> construit la char **cmd valide(stop a delim / pipe)
	2. get_pipe_token -> avance le token
*/
t_cmd	*init_commands_t_cmd(t_token *tokens)
{
	char	**cmd;
	char	**prompt_cmd;
	t_cmd	*head;
	t_cmd	*new;

	cmd = NULL;
	prompt_cmd = NULL;
	head = NULL;
	while(tokens)
	{
		cmd = malloc_cmd(tokens);
		if (!cmd)
			return (NULL);
		prompt_cmd = build_cmd(tokens, cmd);
		init_redir(tokens, new);
		tokens = to_pipe_token(tokens);
		if (!tokens)
		{
			new = new_cmd(prompt_cmd);
			cmd_add_back(&head, new);
			free(prompt_cmd);
			break ; //cannot break if ... | grep file
		}
		new = new_cmd(prompt_cmd);
		cmd_add_back(&head, new);
		free(prompt_cmd);
		tokens = tokens->next;
	}
	print_cmd_struct(head);
	return (head);
}
