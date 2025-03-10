/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:17:37 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/10 11:19:05 by abarahho         ###   ########.fr       */
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

// void	print_redir(t_redir *redir)
// {
// 	t_redir *current_redir = redir;

// 	while (current_redir)
// 	{
// 		printf("  Redirection: Type \"%s\"", current_redir->value);
// 		if (current_redir->file)
// 			printf(", File \"%s\"", current_redir->file);
// 		if (current_redir->append)
// 			printf(" (Append)");
// 		if (current_redir->heredoc)
// 			printf(" (Heredoc, Delimiter \"%s\")", current_redir->delimiter);
// 		printf("\n");
// 		current_redir = current_redir->next;
// 	}
// }

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
	new = NULL;
	while(tokens)
	{
		cmd = malloc_cmd(tokens);
		if (!cmd)
			return (NULL);
		prompt_cmd = build_cmd(tokens, cmd);
		new = new_cmd(prompt_cmd);
		cmd_struct_add_back(&head, new);
		init_redirs(tokens, new);
		tokens = to_pipe_or_last_token(tokens);
		// print_cmd(new->cmd);
		tokens = tokens->next;
		// free_prompt(prompt_cmd);
	}
	// print_cmd_struct(head);
	return (head);
}
