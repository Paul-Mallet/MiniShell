/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:15:15 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/23 16:52:15 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executing.h"

// t_redir	*new_redir(t_token *tokens)
// {
// 	t_redir	*new;

// 	new = (t_redir *)malloc(sizeof(t_redir));
// 	if (!new)
// 		return (NULL);
// 	new->file = NULL; 
// 	new->fd = 0;
// 	new->append = false;
// 	new->is_heredoc = false;
// 	new->delimiter = NULL;
// 	return (new);
// }

// void	redir_add_back(t_redir **lst, t_redir *new)
// {
// 	t_redir	*current;

// 	if (!lst || !new)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	current = *lst;
// 	while (current->next != NULL)
// 		current = current->next;
// 	current->next = new;
// 	new->prev = current;
// }

// void free_redir(t_redir **redirs)
// {
//     t_redir *current;
//     t_redir *next;

//     if (!redirs || !*redirs)
//         return;
//     current = *redirs;
//     while (current)
//     {
//         next = current->next;
//         free(current->file);
// 		free(current->delimiter);
//         free(current);
//         current = next;
//     }
//     *redirs = NULL;
// }