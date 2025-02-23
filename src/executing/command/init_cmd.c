/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:17:37 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/23 17:34:16 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"
#include "../../../includes/parsing.h"

void print_cmd(char **cmd)
{
	int i; 
	
	i = 0;
	if (!cmd)
		return ;
	while(cmd[i])
	{
		printf("%s\n", cmd[i++]);
	}
}

int	cmd_size(t_token *tokens)
{
	int	size;

	size = 0;
	while (tokens)
	{		
		if (tokens->subtype == CMD || tokens->subtype == ARG)
			size++;
		if (tokens->type == PIPE || tokens->subtype == DELIM)
			break ;
		tokens = tokens->next;
	}
	return (size);
}

char	**build_cmd(t_token	*tokens) //["value1", "value2"]
{
	char	**cmd;
	int		i;
	int		size;
	bool	cmd_found;

	if (!tokens)
		return (NULL);
	i = 0;
	cmd_found = false;
	size = cmd_size(tokens);
	cmd = (char **)malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
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
	while (tokens->next)
	{
		if (tokens->subtype == IS_PIPE)
			break ;
		tokens = tokens->next;
	}
	return (tokens);
}

/*
	1. build_cmd -> construit la char **cmd valide(stop a delim / pipe)
	2. get_pipe_token -> avance le token
*/
void	init_commands_t_cmd(t_token *tokens)
{
	char	**prompt_cmd;

	prompt_cmd = NULL;
	while(tokens)
	{
		prompt_cmd = build_cmd(tokens);
		// if (!prompt_cmd)
		// 	break ; //?, if failed, check next pipe
		tokens = to_pipe_token(tokens); //? t_token *
		if (!tokens)
			break ;
		print_cmd(prompt_cmd);
		printf("\n\n");
		free (prompt_cmd);
		tokens = tokens->next;
	}
}