/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:17:37 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/26 12:45:45 by pamallet         ###   ########.fr       */
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

t_token	*to_pipe_or_last_token(t_token *tokens)
{
	while (tokens->next)
	{
		if (tokens->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (tokens);
}

/*
	init_cmds_struct
	1. build_cmd -> construit la char **cmd valide(stop a delim / pipe)
	2. get_pipe_token -> avance le token
*/
t_cmd	*init_cmd_struct(t_token *tokens)
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
		init_new_redir(tokens, new);
		tokens = to_pipe_or_last_token(tokens);
		// if (!tokens)
		// {
		// 	new = new_cmd(prompt_cmd);
		// 	cmd_struct_add_back(&head, new);
		// 	free(prompt_cmd);
		// 	break ; //cannot break if ... | grep file
		// }
		new = new_cmd(prompt_cmd);
		cmd_struct_add_back(&head, new);
		free(prompt_cmd);
		tokens = tokens->next;
	}
	print_cmd_struct(head);
	return (head);
}
