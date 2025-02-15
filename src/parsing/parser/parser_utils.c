/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:38:47 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/15 11:43:34 by paul_mallet      ###   ########.fr       */
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
