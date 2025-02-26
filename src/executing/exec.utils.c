/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:25:23 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/26 19:01:58 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"

int	count_cmds(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		if (cmds->is_builtin == true)
			i++;
		cmds = cmds->next;
	}
	return (i);
}