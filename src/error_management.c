/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:49:07 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/11 12:06:17 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"

int	error_handling(t_error_code code, char *cmd)
{
	if (code == ERR_FILE_NOT_FOUND)
		return (ft_dprintf(2, "\n%s: No such file or directory\n", cmd));
	else if (code == ERR_ARGS)
		return (ft_dprintf(2, "\ninvalid number of arguments.\n"));
	// else if (code == ERR_REDIRS)
	// 	return (ft_dprintf(2, "invalid redirections.\n"));
	else if (code == ERR_PERMISSION_DENIED)
		return (ft_dprintf(2, "\n%s: Permission denied\n", cmd));
	else if (code == ERR_CMD_NOT_FOUND)
		return (ft_dprintf(2, "\n%s: command not found\n", cmd));
	else if (code == ERR_DOUBLE_PIPES)
		return (ft_dprintf(2, "\n%s: invalid double pipes\n", cmd));
	else if (code == ERR_PIPE_FAILURE)
		return (ft_dprintf(2, "\n'|': pipe failure\n"));
	else if (code == ERR_FORK_FAILURE)
		return (ft_dprintf(2, "\nfork failure\n"));
	else if (code == ERR_UNCLOSED_QUOTES)
		return (ft_dprintf(2, "\n%s: unclosed quotes\n", cmd));
	else
		return (ft_dprintf(2, "\nunknown error\n"));
	return (1);
}
