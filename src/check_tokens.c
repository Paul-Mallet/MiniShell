/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:18:28 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/18 14:55:56 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "builtins.h"
#include "parsing.h"
#include "executing.h"
#include "signals.h"


// static bool	return_false(t_data *data, t_token *token)
// {
// 	error_handling(SYNTAX_ERROR_NEAR_TOKEN, token->value);
// 	data->exit_code = 2;
// 	return (false);
// }

// bool check_tokens(t_data *data)
// {
//     t_token *current;

//     if (!data->tokens)
//         return (false);
    
//     current = data->tokens;
//     while (current)
//     {
//         if (current->type == REDIR)
//         {
//             if (!current->next || (current->next->type != WORD && current->next->type != SEPARATOR))
// 				return (return_false(data, current));
//             if (current->next && current->next->type == REDIR)
//             	return (return_false(data, current));
//         }
//         if (!current->next && current->type == REDIR)
// 			return (return_false(data, current));
//         if (current->type == REDIR && current->next && current->next->type == REDIR)
// 			return (return_false(data, current));
//         if (current->type == WORD && current->next && current->next->type == REDIR)
// 			return (return_false(data, current));
//         current = current->next;
//     }
//     return (true);
// }
