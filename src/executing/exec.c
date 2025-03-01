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

// void	exec(t_data *data)
// {
// 	int	nb_cmd;
// 	int	i;

// 	i = 0;
// 	check_heredoc(data);
// 	ft_builtins(data);
// 	nb_cmd = count_cmds(data->cmds);
// 	while (i < nb_cmd - 1)
// 	{
// 		exec_command(data);
// 		i++;
// 	}

// }

// void	check_heredoc(t_data *data)
// {
// 	t_cmd	*current;
// 	t_redir	*current_redir;

// 	current = data->cmds;
// 	current_redir = data->cmds->redir;
// 	while (current)
// 	{
// 		while (current_redir)
// 		{
// 			if (current_redir->heredoc)
// 			{
// 				if (!redir_heredoc(current_redir))
// 				data->exit_code = 0;
// 			}
// 			current_redir = current_redir->next;
// 		}
// 		current = current->next;
// 	}
// }

// int	exec_command(t_data *data)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
	
// }
