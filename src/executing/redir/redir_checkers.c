/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:54:11 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/05 17:25:48 by abarahho         ###   ########.fr       */
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
	char	*line;
	int		og_stdin;

	og_stdin = dup(STDIN_FILENO);
	if (og_stdin == -1)
	{
		perror("dup");
		return(false);
	}
	if (!heredoc_name(redir))
		return (false);
	while (1)
	{
		line = readline("heredoc>");
		if (ft_strcmp(line, redir->delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
		free(line);
	}
	dup2(og_stdin, STDIN_FILENO);
	close (og_stdin);
	unlink(redir->file);
	free(redir->file);
	return (true);
}

void	*heredoc_name(t_redir *redir)
{
	char		*hd_file;
	static int	i;
	char		*num;

	i++;
	num = ft_itoa(i);
	hd_file = join_lines("heredoc_", num);
	if (!hd_file)
	{
        free(num);
        return NULL;
    }
	redir->fd = open(hd_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
	{
		free(hd_file);
		free(num);
		heredoc_name(redir);
	}
	redir->file = hd_file;
	free(num);
	return (hd_file);
}
