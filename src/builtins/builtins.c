/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:46:29 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/19 16:34:25 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "executing.h"

/*
	builtins conditions
	1. input is already parsed(trim, cmds, args validation)
	2. check input fit builtins names(strcmp)
	3. send input without builtins(strchr + 1, skip ' ')
// */

void	ft_builtins(t_data *data, t_cmd *cmds)
{
	//handle cmd[1] -> -option, no option
	if (!ft_strcmp(cmds->cmd[0], "echo"))
		ft_echo(data, cmds->cmd);
	if (!ft_strcmp(cmds->cmd[0], "cd"))
		ft_cd(data, data->env, cmds->cmd[1]);
	if (!ft_strcmp(cmds->cmd[0], "pwd"))
		ft_pwd(data);
	if (!ft_strcmp(cmds->cmd[0], "export"))
		ft_export(data, cmds->cmd);
	if (!ft_strcmp(cmds->cmd[0], "unset"))
		ft_unset(data, cmds->cmd);
	if (!ft_strcmp(cmds->cmd[0], "env"))
		ft_env(data, cmds);
	if (!ft_strcmp(cmds->cmd[0], "exit"))
		ft_exit(data, cmds);
}
