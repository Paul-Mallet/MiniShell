/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:46:29 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/19 20:32:27 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "executing.h"

void	ft_builtins(t_data *data, t_cmd *cmds)
{
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
