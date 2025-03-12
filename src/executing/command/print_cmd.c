/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:16:25 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/12 14:35:12 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"
#include "../../../includes/executing.h"

void print_cmds(char **cmds)
{
	while(*cmds != NULL)
		printf("cmd_struct: %s\n", *cmds++);
}

void print_redir(t_redir *redir)
{
	printf("\n\nContent of redir: \nFile: %s\nValue: %s\nAppend: %d\nHeredoc: %d\nDelim: %s\n\n",
			redir->file, redir->value, redir->append, redir->heredoc, redir->delimiter);
}

void print_cmd_struct(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while(current)
	{
		print_cmds(cmds->cmd);
		printf("\n\n");
		while (cmds->redir)
		{
			print_redir(cmds->redir);
			current->redir = current->redir->next;
		}
		current = current->next;
	}
}
