/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:28:40 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/14 11:39:01 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

t_token	*ft_lexer(char *input)
{
    t_token	*tokens;
    int		i;

    i = 0;
    tokens = NULL;
    while (input[i])
    {
		if (input[i] == '|')
			tokens = is_a_pipe(input, &i);
		if (input[i] == '<' || input[i] == '>')
			tokens = is_a_redir(input, &i);
		if (!ft_isdigit(input[i]))
			tokens = is_a_word(input, &i);
    }
    return (tokens);
}
