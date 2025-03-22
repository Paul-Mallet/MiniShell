/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:10 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/22 16:12:55 by abarahho         ###   ########.fr       */
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
			printf("minishell: exit: %s: numeric argument required\n", cmd);
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

// opti ctr_exit_d with ft_exit
// exit in child process + echo $? in parent must display return(%256)
void	ft_exit(t_data *data, t_cmd *cmds, bool is_simple_cmd)
{
	printf("\nexit\n");
	if (cmds)
	{
		if (cmds->cmd[1])
		{
			if (check_numeric_arg(cmds->cmd[1]))
				data->exit_code = ft_atoi(cmds->cmd[1]);
			else
			{
				if (!is_simple_cmd)
					free(data->pids);
				data->exit_code = 2;
				free_data(data);
				exit((unsigned char)data->exit_code);
			}
		}
		if (count_args(cmds->cmd) > 2 && check_numeric_arg(cmds->cmd[1]))
		{
			printf("minishell: exit: too many arguments\n");
			data->exit_code = 1;
			return ;
		}
	}
	if (!is_simple_cmd)
		free(data->pids);
	free_data(data);
	exit((unsigned char)data->exit_code % 256);
}
