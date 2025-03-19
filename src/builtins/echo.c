/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:44 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 05:16:18 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#include <stdbool.h>

bool check_large_n(char *n)
{
	int i;

	i = 0;
	if (!n || n[i] != '-')
		return false;
	i++;
	if (n[i] == '\0')
		return false;
	while (n[i])
	{
		if (n[i] != 'n')
			return false;
		i++;
	}
	return true;
}


int	ft_echo(t_data *data, char **cmds)
{
	bool	arg_n;
	int		i;

	i = 0;
	arg_n = false;
	i++;
	while (cmds[i])
	{
		if (!ft_strcmp(cmds[i], "-n") && cmds[i][1] == 'n')
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
	if (!ft_echo_next(data, cmds, i, arg_n))
		return (0);
	data->exit_code = 2;
	return (1);  // error a implementer
}

int	ft_echo_next(t_data *data, char **cmd, int i, bool arg_n)
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
	data->exit_code = 0;	//always true
	return (0);
}
