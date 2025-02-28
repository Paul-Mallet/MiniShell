/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:54:11 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/28 14:53:06 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executing.h"

bool	redir_input(t_redir *redir, bool last_cmd)
{
	redir->fd = open(redir->file, O_RDONLY);
	if (redir->fd == -1)
	{
		perror("open");
		return (false);
	}
	if (last_cmd)
		dup2(redir->fd, STDIN_FILENO);
	close(redir->fd);
	return (true);
}

bool	redir_output(t_redir *redir, bool last_cmd)
{
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
	{
		perror("open");
		return (false);
	}
	if (last_cmd)
		dup2(redir->fd, STDOUT_FILENO);
	close(redir->fd);
	return (true);
}


bool	redir_heredoc(t_redir *redir, bool last_cmd)
{
	char	*line;

	redir->fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
	{
		perror("open");
		return (false);
	}
	while (1)
	{
		line = get_next_line(STDIN_FILENO); // Lire entree standard
		if (ft_strcmp(line, (redir->delimiter + '\n')) == 0)
		{
			free (line);
			break ;
		}
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
		free(line);
	}
	if (last_cmd)
		dup2(redir->fd, STDIN_FILENO);
	close(redir->fd);
	return (true);
}

bool	redir_append(t_redir *redir, bool last_cmd)
{
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd == -1)
	{
		perror("open");
		return (false);
	}
	if (last_cmd)
		dup2(redir->fd, STDOUT_FILENO);
	close(redir->fd);
	return (true);
}