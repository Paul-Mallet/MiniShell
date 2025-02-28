/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:54:11 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/28 17:57:02 by abarahho         ###   ########.fr       */
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

bool	redir_heredoc(t_redir *redir)
{
	char		*line;
	char		*delim;
	char		*hd_file;

	delim = join_lines(redir->delimiter, "\n");
	hd_file = heredoc_name();
	redir->fd = open(hd_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(hd_file);
	if (redir->fd == -1)
	{
		perror("open");
		free(delim);
		return (false);
	}
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			free(delim);
			close(redir->fd);
			return (false);
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
		free(line);
	}
	free(delim);
	dup2(redir->fd, STDIN_FILENO);
	close(redir->fd);
	return (true);
}

char	*heredoc_name(void)
{
	static int	i;
	char		*num;
	char		*hd_file;

	i++;
	num = ft_itoa(i);
	hd_file = join_lines("/tmp/heredoc_", num);
	free(num);
	return (hd_file);
}
