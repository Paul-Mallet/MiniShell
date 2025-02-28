/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:16:25 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/28 16:58:41 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"
#include "../../../includes/executing.h"

void print_cmds(char **cmds)
{
	while(*cmds != NULL)
		printf("%s\n", *cmds++);
}

void print_redir(t_redir *redir)
{
	printf("\n\nContent of redir: \nFile: %s\nValue: %s\nAppend: %d\nHeredoc: %d\nDelim: %s\n\n",
			redir->file, redir->value, redir->append, redir->heredoc, redir->delimiter);
}

void print_cmd_struct(t_cmd *cmd)
{
	while (cmd->redir)
		print_redir(cmd->redir);
	// while(cmd)
	// {
	// 	// print_cmds(cmd->cmd);
	// 	printf("\n\n");
	// 	cmd = cmd->next;
	// }
}
