// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/13 17:26:39 by abarahho          #+#    #+#             */
// /*   Updated: 2025/02/27 17:02:54 by abarahho         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"

void	exec(t_data *data)
{
	int	nb_cmd;

	check_heredoc(data);
	nb_cmd = count_cmds(data->cmds);
	// if (nb_cmd > 1)
	// 	exec_multiple_cmds(data, nb_cmd);
	// exec_simple_cmd(data);
	ft_builtins(data);
	
}

void	check_heredoc(t_data *data)
{
	t_cmd	*current;
	t_redir	*current_redir;

	current = data->cmds;
	current_redir = data->cmds->redir;
	while (current)
	{
		while (current_redir)
		{
			if (current_redir->heredoc)
			{
				if (!redir_heredoc(current_redir))
				data->exit_code = 0;
			}
			current_redir = current_redir->next;
		}
		current = current->next;
	}
}

// t_redir	*current;

// 	current = cmd->redir;


// void	exec_multiple_cmds(t_data *data, int nb_cmd)
// {
// 	while (nb_cmd)
// }

// void	exec_multiple_cmd(t_data *data)
// {
	
// }

// int	exec_command(t_data *data)
// {
// 	pid_t	pid;
// 	//char	*buf = data->cmds->cmd[i];


// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	//
// }
