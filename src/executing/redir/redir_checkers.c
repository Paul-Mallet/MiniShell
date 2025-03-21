/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:54:11 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/21 12:00:37 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"
#include "signals.h"

void	redir_input(t_redir *redir, bool is_last_in, t_data *data)
{
	redir->fd = open(redir->file, O_RDONLY);
	if (redir->fd == -1)
	{
		perror("open");
		data->exit_code = 1;
		close(redir->fd);
		return ;
	}
	if (is_last_in)
	{
		close(STDIN_FILENO);
		if (dup2(redir->fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(redir->fd);
			return ;
		}
	}
	close(redir->fd);
}

void	redir_output(t_redir *redir, bool is_last_out, t_data *data)
{
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
	{
		perror("open");
		data->exit_code = 1;
		close(redir->fd);
		return ;
	}
	if (is_last_out)
	{
		close(STDOUT_FILENO);
		if (dup2(redir->fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(redir->fd);
			return ;
		}
	}
	close(redir->fd);
}

void	redir_append(t_redir *redir, bool is_last_out, t_data *data)
{
	redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd == -1)
	{
		perror("open");
		data->exit_code = 1;
		close(redir->fd);
		return ;
	}
	if (is_last_out)
	{
		close(STDOUT_FILENO);
		if (dup2(redir->fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(redir->fd);
			return ;
		}
	}
	close(redir->fd);
}

void	redir_heredoc(t_redir *redir, bool is_last_in)
{
	redir->fd = open(redir->file, O_RDONLY);
	if (redir->fd < 0)
	{
		perror("Invalid file descriptor before dup2");
		return;
	}
	printf("duplicating %s & fd : %d\n\n", redir->file, redir->fd);
	if (is_last_in)
	{
		printf("id_last in\n");
		close(STDIN_FILENO);
		if (dup2(redir->fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(redir->fd);
			return ;
		}
	}
	printf("closed %s & fd : %d\n\n", redir->file, redir->fd);
	close(redir->fd);
	unlink(redir->file);
}
