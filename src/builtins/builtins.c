/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:46:29 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/07 19:07:30 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

/*
	builtins conditions
	1. input is already parsed(trim, cmds, args validation)
	2. check input fit builtins names(strcmp)
	3. send input without builtins(strchr + 1, skip ' ')
// */

void	ft_builtins(t_data *data, t_cmd *cmds)
{                                                                           
	if (!ft_strcmp(cmds->cmd[0], "echo"))
		ft_echo(cmds->cmd);
	if (!ft_strcmp(cmds->cmd[0], "cd"))
		ft_cd(data->env, cmds->cmd[1]);
	if (!ft_strcmp(cmds->cmd[0], "pwd"))
		ft_pwd();
	if (!ft_strcmp(cmds->cmd[0], "export"))
		ft_export(data->env, cmds->cmd);
	if (!ft_strcmp(cmds->cmd[0], "unset"))
		ft_unset(&data->env, cmds->cmd);
	if (!ft_strcmp(cmds->cmd[0], "env"))
		ft_env(data->env);
	// if (!ft_strcmp(cmds->cmd[0], "exit"))
	// // 	ft_exit(data, input, prompt);
}
