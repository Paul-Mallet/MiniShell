/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:36:08 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/20 15:25:31 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"
#include "signals.h"

void	exec_command(t_cmd *cmds, t_data *data, t_cmd_order nbr, int *i)
{
	pid_t	pid;
	char	*path;

	path = NULL;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		data->char_env = make_env(data->env);
		check_redir(cmds, data);
		if (data->cmds->cmd[0] == NULL)
		{
			free(data->pids);
			printf("error cmd\n");
			close_pipes(cmds);
			free_data(data);
			exit(1);
		}
		// if (is_builtins(cmds->cmd[0]))
		// 	ft_builtins(data, cmds);
		path = check_path(data, cmds->cmd[0]); //! "echo"
		if (!path)
		{
			close_pipes(cmds);
			free(data->pids);
			free_data(data);
			exit(data->exit_code);
		}
		executing_command(cmds, path, data, nbr);
	}
	data->pids[*i] = pid;
	*i += 1;
}

void	exec_simple_cmd(t_data *data)
{
	pid_t	pid;
	int		status;
	
	if (is_builtins(data->cmds->cmd[0]) && !data->cmds->redir)
		ft_builtins(data, data->cmds);
	else 
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			data->char_env = make_env(data->env);
			check_redir(data->cmds, data);
			if (data->cmds->cmd[0] == NULL)
			{
				free_simple_cmd(data);
				exit(1);
			}
			executing_simple_cmd(data);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = 128 + WTERMSIG(status);
		}
	}
}
