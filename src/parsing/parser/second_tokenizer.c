/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:09:37 by paul_mallet       #+#    #+#             */
/*   Updated: 2025/02/17 14:14:18 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

// t_token *second_tokenization(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		if (tokens->type == WORD
// 			&& tokens->value[0] == '-')
// 			tokens->subtype = ARG;
// 			//echo -n -n -n test -> test%
// 			//echo -nnn test -> test%
// 			//echo -npn test -> pn test%
// 		else if (tokens->type == WORD
// 			&& tokens->next->next->type == REDIR) //not allowed HEREDOC & APPEND
// 			tokens->subtype = FILES;
// 		else if (tokens->value == '<'
// 			&& tokens->prev->prev->subtype == FILES)
// 			tokens->subtype = REDIR_INPUT;
// 		else if (tokens->value == '>'
// 			&& tokens->prev->prev->subtype == FILES)
// 			tokens->subtype = REDIR_OUTPUT;
// 		else if (tokens->type == REDIR
// 			&& !ft_strcmp(tokens->value, ">>"))
// 			tokens->subtype = APPEND;
// 		else if (tokens->type == REDIR
// 			&& !ft_strcmp(tokens->value, "<<"))
// 			tokens->subtype = HEREDOC;
// 		else if (tokens->type == WORD
// 			&& tokens->prev->prev->subtype == HEREDOC
// 			&& ft_is_all_alnum(tokens->value)) //split <<DELIM -> << DELIM
// 			tokens->subtype = DELIM;
// 		else if ()
// 			tokens->subtype = CMD;
// 		else
// 			//handle_errors();
// 		tokens = tokens->next;
// 	}
// }
