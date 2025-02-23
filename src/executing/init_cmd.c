/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:17:37 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/23 15:18:16 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include "../../includes/parsing.h"

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

char	**build_cmd(t_token	*tokens, int size)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = (char **)malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
	while (tokens)
	{
		if (tokens->subtype == CMD || tokens->subtype == ARG)
			cmd[i++] = ft_strdup(tokens->value);
		if (tokens->type == PIPE || tokens->subtype == DELIM)
			break ;
		tokens = tokens->next;
	}
	cmd[i] = NULL;
	return (cmd);
}


void	init_cmds(t_data *data)
{
	int		size;
	char	**cmd;

	size = cmd_size(data->tokens);
	cmd = build_cmd(data->tokens, size);
	print_cmd(cmd);
}