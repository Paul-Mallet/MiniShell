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

// #include "../../includes/minishell.h"
// #include "../../includes/executing.h"

// void	exec(t_data *data)
// {
// 	// int	nb_cmd;

// 	redir_managing(data);
// 	// nb_cmd = count_cmd(data->cmds);
// 	// if (nb_cmd > 1)
// 	// 	exec_multiple_cmds(data, nb_cmd);
// 	// exec_simple_cmd(data);
// 	ft_builtins(data);
	
// }

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

// int	file_to_pipe(char *file, t_ppx *ppx)
// {
// 	int	file_fd;

// 	file_fd = open(file, O_RDONLY);
// 	if (file_fd == -1)
// 		return (perror(file), 0);
// 	dup2(file_fd, STDIN_FILENO);
// 	dup2(ppx->pipe_fd[1], STDOUT_FILENO);
// 	close(file_fd);
// 	close_pipe(ppx);
// 	return (1);
// }

// int	pipe_to_file(char *file, t_ppx *ppx)
// {
// 	int	file_fd;

// 	file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (file_fd == -1)
// 		return (perror(file), 0);
// 	dup2(ppx->pipe_fd[0], STDIN_FILENO);
// 	dup2(file_fd, STDOUT_FILENO);
// 	close(file_fd);
// 	close_pipe(ppx);
// 	return (1);
// }