/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:45:28 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/26 15:15:56 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"

// bool	is_pipe_token(t_token *token)
// {
// 	return (token->type == PIPE);
// }

// bool	is_redir_token(t_token *token)
// {
// 	return (token->type == REDIR);
// }

// bool	is_word(t_token *token)
// {
// 	return (token->type == WORD);
// }

// bool	check_pipes(t_token *tokens)
// {
// 	t_token	*current;
// 	bool	last_was_pipe;

// 	current = tokens;
// 	last_was_pipe = false;
// 	if (is_pipe_token(current))
// 	{
// 		printf("Error: Command cannot start with a pipe '|'.\n");
// 		return (false);
// 	}
// 	while (current)
// 	{
// 		if (is_pipe_token(current))
// 		{
// 			if (last_was_pipe)
// 			{
// 				printf("Error: Two consecutive pipes '|' detected.\n");
// 				return (false);
// 			}
// 			last_was_pipe = true;
// 		}
// 		else
// 			last_was_pipe = false;
// 		current = current->next;
// 	}
// 	if (last_was_pipe)
// 	{
// 		printf("Error: Command cannot end with a pipe '|'.\n");
// 		return (false);
// 	}
// 	return (true);
// }

// bool	check_redirections(t_token *tokens)
// {
// 	t_token	*current;

// 	current = tokens;
// 	while (current)
// 	{
// 		if (is_redir_token(current))
// 		{
// 			if (current->next || current->next->subtype != FILES
// 				|| current->next->subtype != DELIM)
// 			{
// 				printf("Error: Redirection '%s' without a valid file.\n", current->value);
// 				return (false);
// 			}
// 			if (is_pipe_token(current->next))
// 			{
// 				printf("Error: Redirection '%s' cannot be followed by a pipe '|'.\n", current->value);
// 				return (false);
// 			}
// 		}
// 		current = current->next;
// 	}
// 	return (true);
// }

// bool	check_tokens(t_token *tokens)
// {
// 	if (!check_pipes(tokens))
// 		return (false);
// 	if (!check_redirections(tokens))
// 		return (false);
// 	return (true);
// }
