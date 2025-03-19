/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:37:38 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/19 15:42:36 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"
#include "signals.h"

void	check_heredoc(t_data *data)
{
	t_token	*current;
	bool	is_heredoc;

	is_heredoc = false;
	current = data->tokens;
	while (current)
	{
		if (current->subtype == HEREDOC)
			is_heredoc = true;
		current = current->next;
	}
	if (is_heredoc)
		fork_heredoc(data);
}

void	fork_heredoc(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		data->exit_code = 1;
		return ;
	}
	else if (pid == 0)
	{
		heredoc_managing(data);
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
}

void	heredoc_managing(t_data *data)
{
	t_cmd	*current;
	t_redir	*current_redir;

	current = data->cmds;
	while (current)
	{
		current_redir = current->redir;
		while (current_redir)
		{
			if (current_redir->heredoc)
				write_heredoc(current_redir);
			current_redir = current_redir->next;
		}
		current = current->next;
	}
}

bool	write_heredoc(t_redir *redir)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	heredoc_filename(redir);
	while (1)
	{
		line = readline("heredoc>");
		if (!line)
			break;
		if (ft_strcmp(line, redir->delimiter) == 0)	//1.
		{
			free(line);
			break ;
		}
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
		free(line);
	}
	close(redir->fd);
	return (true);
}

void	heredoc_filename(t_redir *redir)
{
	char		*hd_file;
	char		*num;
	static int	i;

	i++;
	num = ft_itoa(i);
	hd_file = join_lines("heredoc_", num);
	if (!hd_file)
	{
		free(num);
		return ;
	}
	redir->fd = open(hd_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
	{
		free(hd_file);
		free(num);
		heredoc_filename(redir);
	}
	free(redir->file);
	redir->file = ft_strdup(hd_file);
	free(hd_file);
	free(num);
}
