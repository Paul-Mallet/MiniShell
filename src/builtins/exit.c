/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:10 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 07:22:21 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"

int	check_numeric_arg(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_isdigit(cmd[i]))
		{
			printf("bash: exit: %s: numeric argument required\n", cmd);
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

//opti ctr_exit_d with ft_exit
void	ft_exit(t_data *data, t_cmd *cmd)
{
	printf("\nexit\n");
	if (data->cmds)
	{
		if (data->cmds->cmd[1])
		{
			if (check_numeric_arg(data->cmds->cmd[1]))
				data->exit_code = ft_atoi(data->cmds->cmd[1]);
			else
				data->exit_code = 2;
		}
		if (count_args(cmd->cmd) > 2 && check_numeric_arg(data->cmds->cmd[1]))
		{
			data->exit_code = 1;
			printf("bash: exit: too many arguments\n");
			return ;
		}
	}
	free_exit(data);
	exit((unsigned char)data->exit_code % 256);
}
