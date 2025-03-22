/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:44 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/22 11:52:48 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"

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

	i = 1;
	arg_n = false;
	while (cmds[i] != NULL)
	{
		if (!ft_strcmp(cmds[i], "-n") || check_large_n(cmds[i]))
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

int	ft_echo_next(t_data *data, char **cmd, int i, bool arg_n)
{
	while (cmd[i] != NULL)
	{
		if (contains_exclam(cmd[i]))
		{
			data->exit_code = 127;
			return (0);
		}
		if (cmd[i][0] == '\0')
			printf(" ");
		else
			printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!arg_n)
		printf("\n");
	data->exit_code = 0;
	return (1);
}
