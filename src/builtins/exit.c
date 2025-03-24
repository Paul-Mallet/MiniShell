/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:10 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/24 13:19:15 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"

// exit 42 inside sub ./minishell
// exit q
int	check_numeric_arg(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_isdigit(cmd[i]))
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
				cmd);
			return (0);
		}
	}
	return (1);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	exit_simple_cmd(t_data *data, bool is_simple_cmd)
{
	if (!is_simple_cmd)
		free(data->pids);
	data->exit_code = 2;
	free_data(data);
	exit((unsigned char)data->exit_code);
}

void	ft_exit(t_data *data, t_cmd *cmds, bool is_simple_cmd)
{
	if (is_simple_cmd)
		printf("exit\n");
	if (cmds)
	{
		if (cmds->cmd[1])
		{
			if (check_numeric_arg(cmds->cmd[1]))
				data->exit_code = ft_atoi(cmds->cmd[1]);
			else
				exit_simple_cmd(data, is_simple_cmd);
		}
		if (count_args(cmds->cmd) > 2 && check_numeric_arg(cmds->cmd[1]))
		{
			ft_dprintf(2, "minishell: exit: too many arguments\n");
			data->exit_code = 1;
			return ;
		}
	}
	if (!is_simple_cmd)
		free(data->pids);
	free_data(data);
	exit((unsigned char)data->exit_code % 256);
}
