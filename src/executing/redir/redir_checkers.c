/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:54:11 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/13 18:10:09 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executing.h"
#include "../../../includes/signals.h"

bool	redir_input(t_redir *redir, bool is_last_in)
{
	redir->fd = open(redir->file, O_RDONLY);
	if (redir->fd == -1)
	{
		perror("open");
		return (false);
	}
	if (is_last_in)
		dup2(redir->fd, STDIN_FILENO);
	close(redir->fd);
	return (true);
}

bool	redir_output(t_redir *redir, bool is_last_out)
{
	printf("JE SUIS LA ");
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("JE SUIS LA 1");
	if (redir->fd == -1)
	{
		printf("JE SUIS LA 2");
		perror("open");
		return (false);
	}
	printf("JE SUIS LA 3");
	if (is_last_out)
	{
		if (dup2(redir->fd, STDOUT_FILENO) == -1)
		{
			printf("JE SUIS LA 5");
			close(redir->fd);
			return (false);
		}
	}
	close(redir->fd);
	return (true);
}

bool	redir_append(t_redir *redir, bool is_last_out)
{
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd == -1)
	{
		perror("open");
		return (false);
	}
	if (is_last_out)
		dup2(redir->fd, STDOUT_FILENO);
	close(redir->fd);
	return (true);
}

bool	redir_heredoc(t_redir *redir, bool is_last_in)
{
	redir->fd = open(redir->file, O_RDONLY);
	if (redir->fd == -1)
	{
		perror("open");
		return (false);
	}
	if (is_last_in)
		dup2(redir->fd, STDIN_FILENO);
	unlink(redir->file);
	close(redir->fd);
	return (true);
}
