/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:40:55 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/27 12:06:40 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executing.h"

void	redir_managing(t_data *data)
{
	t_cmd	*current;

	current = data->cmds;
	while (current)
	{
		open_redir(current);
		current = current->next;
	}
}

void	open_redir(t_cmd *cmd)
{
	t_redir	*current;

	current = cmd->redir;
	while (current)
	{
		if (current->file && current->in_redir)
		{
			current->fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (current->fd == -1)
			{
				perror("open");
				return ;
				// exit code
			}
			close(current->fd);
		}
		current = current->next;
	}
}

// void	open_redir_next(t_redir *redir)
// {
// 	int		target_fd;

// 	target_fd = STDOUT_FILENO;
// 	if (redir->append)
// 		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else if (redir->heredoc)
// 	{
// 		target_fd = STDIN_FILENO;
// 		handle_heredoc(redir->delimiter);
// 	}
// 	else
// 		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (redir->fd == -1)
// 	{
// 		perror("open");
// 		return ;
// 		// exit code
// 	}
// 	if (dup2(redir->fd, target_fd) == -1)
// 	{
// 		perror("dup2");
// 		return ;
// 		// exit code
// 	}
// 	close(redir->fd);
// }

// void	handle_heredoc(char *delimiter)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("open heredoc");
// 		return ;
// 		// exit code
// 	}
// 	while (1)
// 	{
// 		line = get_next_line(STDIN_FILENO); // Lire entree standard
// 		if (ft_strcmp(line, delimiter) == 0)
// 			break ;
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	close(fd);
// }
