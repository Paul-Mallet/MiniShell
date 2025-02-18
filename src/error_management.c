/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:49:07 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 18:58:01 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"

int	error_handling(t_error_code code)
{
	// if (code == ERR_FILE_NOT_FOUND)
		// return (ft_dprintf(2, "%s: No such file or directory\n", cmd));
	if (code == ERR_ARGS)
		return (ft_dprintf(2, "invalid number of arguments.\n"));
	// else if (code == ERR_PERMISSION_DENIED)
		// return (ft_dprintf(2, "%s: Permission denied\n", cmd));
	// else if (code == ERR_CMD_NOT_FOUND)
		// return (ft_dprintf(2, "%s: command not found\n", cmd));
	else if (code == ERR_PIPE_FAILURE)
		return (ft_dprintf(2, "pipe failure\n"));
	else if (code == ERR_FORK_FAILURE)
		return (ft_dprintf(2, "fork failure\n"));
	else if (code == ERR_UNCLOSED_QUOTES)
		return (ft_dprintf(2, "unclosed quotes\n"));
	else
		return (ft_dprintf(2, "unknown error\n"));
	return (1);
}
