/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:46:29 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/22 17:01:52 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "executing.h"

void	save_stdin_stdout(t_data *data)
{
	data->stdin = dup(STDIN_FILENO);
	data->stdout = dup(STDOUT_FILENO);
}

void	restore_stdin_stdout(t_data *data)
{
	dup2(data->stdin, STDIN_FILENO);
	close(data->stdin);
	dup2(data->stdout, STDOUT_FILENO);
	close(data->stdout);
}

void	ft_builtins(t_data *data, t_cmd *cmds, bool is_simple_cmd)
{
	if (is_simple_cmd)
	{
		save_stdin_stdout(data);
		check_redir(cmds, data);
		restore_stdin_stdout(data);
	}
	if (!ft_strcmp(cmds->cmd[0], "echo"))
		ft_echo(data, cmds->cmd);
	if (!ft_strcmp(cmds->cmd[0], "cd"))
		ft_cd(data, data->env, cmds->cmd[1]);
	if (!ft_strcmp(cmds->cmd[0], "pwd"))
		ft_pwd(data, cmds);
	if (!ft_strcmp(cmds->cmd[0], "export"))
		ft_export(data, cmds->cmd);
	if (!ft_strcmp(cmds->cmd[0], "unset"))
		ft_unset(data, cmds->cmd);
	if (!ft_strcmp(cmds->cmd[0], "env"))
		ft_env(data, cmds);
	if (!ft_strcmp(cmds->cmd[0], "exit"))
		ft_exit(data, cmds);
}
