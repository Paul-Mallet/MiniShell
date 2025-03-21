/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:16:25 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/21 16:33:59 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executing.h"

// void print_cmds(char **cmds)
// {
// 	printf("\ntry to print cmds\ncmd[0]: %s\n", cmds[0]);
// 	while(*cmds != NULL)
// 		printf("cmd_struct: %s\n", *cmds++);
// }

// void print_redir(t_redir *redir)
// {
// 	printf("\n\nContent of redir: \n");
// 	if (redir->file)
// 		printf("File: %s\n", redir->file);
// 	else
// 		printf("File: (null)\n");
// 	if (redir->value)
// 		printf("Value: %s\n", redir->value);
// 	else
// 		printf("Value: (null)\n");
// 	printf("Append: %d\n", redir->append);
// 	printf("Heredoc: %d\n", redir->heredoc);
// 	if (redir->delimiter)
// 		printf("Delim: %s\n", redir->delimiter);
// 	else
// 		printf("Delim: (null)\n");
// 	printf("\n");
// }

// void print_cmd_struct(t_cmd *cmds)
// {
// 	t_cmd	*current;
// 	t_redir	*cur_redir;
// 	int		i = 0;

// 	current = cmds;
// 	while(current)
// 	{
// 		printf("\ncmd number: %d\n", i++);
// 		cur_redir = current->redir;
// 		print_cmds(current->cmd);
// 		while (cur_redir)
// 		{
// 			print_redir(cur_redir);
// 			cur_redir = cur_redir->next;
// 		}
// 		current = current->next;
// 	}
// }
