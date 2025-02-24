/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:25:23 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/24 18:03:01 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"

int	count_cmds(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->subtype == CMD)
			i++;
		tokens = tokens->next;
	}
	return (i);
}