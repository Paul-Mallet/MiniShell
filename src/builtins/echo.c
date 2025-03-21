/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:44 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/21 19:03:46 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

bool	check_large_n(char *n)
{
	int	i;

	i = 0;
	if (!n || n[i] != '-')
		return (false);
	i++;
	if (n[i] == '\0')
		return (false);
	while (n[i])
	{
		if (n[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	ft_echo(t_data *data, char **cmds)
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
			break ;
	}
	if (ft_echo_next(data, cmds, i, arg_n))
		return ;
}

int	contains_exclam(char *cmd)
{
	int		i;
	char	*from_exclam;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '!')
		{
			from_exclam = &cmd[i];
			ft_printf("minishell: %s: event not found\n", from_exclam);
			return (1);
		}
	}
	return (0);
}

// echo "$"
int	ft_echo_next(t_data *data, char **cmd, int i, bool arg_n)
{
	while (cmd[i])
	{
		if (contains_exclam(cmd[i]))
		{
			data->exit_code = 127;
			return (0);
		}
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
	data->exit_code = 0;
	return (1);
}
