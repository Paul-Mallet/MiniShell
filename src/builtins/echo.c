/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:44 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/10 12:12:47 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

bool	check_large_n(char *n)
{
	int	i;

	i = 0;
	if (n[i] != '-')
		return (false);
	i++;
	while(n[i])
	{
		if (n[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(char **cmds)
{
	bool	arg_n;
	int		i;

	i = 0;
	arg_n = false;
	i++;
	while (cmds[i])
	{
		if (!ft_strcmp(cmds[i], "-n"))
		{
			arg_n = true;
			i++;
		}
		else if (check_large_n(cmds[i]))
		{
			arg_n = true;
			i++;
		}
		else
			break;
	}
	if (!ft_echo_next(cmds, i, arg_n))
		return (0); 
	return (1);  // error a implementer
}

int	ft_echo_next(char **cmd, int i, bool arg_n)
{
	while(cmd[i])
	{
		if (!ft_strcmp(cmd[i], "\0"))
		{
			printf(" ");
			i++;
		}
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!arg_n)
	printf("\n");
	return (0);
    return (0);
}
