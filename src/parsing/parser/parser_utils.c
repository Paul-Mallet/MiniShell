/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:38:47 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/14 19:16:57 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

void	print_token(t_token *token)
{
	while (token)
	{
		printf("Type: %d\n", token->type);
		printf("Value: %s\n", token->value);
		token = token->next;
	}
}
