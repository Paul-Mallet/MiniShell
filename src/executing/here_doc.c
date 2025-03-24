/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:37:38 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/24 11:46:23 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"
#include "signals.h"

int	check_heredoc(t_data *data)
{
	t_cmd	*current_cmd;
	t_redir	*current_redir;

	current_cmd = data->cmds;
	while (current_cmd)
	{
		current_redir = current_cmd->redir;
		while (current_redir)
		{
			if (current_redir->heredoc)
			{
				heredoc_filename(current_redir);
				if (fork_heredoc(current_redir, data) != 0)
					return (EXIT_FAILURE);
			}
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
	return (EXIT_SUCCESS);
}

void	child_sigint_handler(int sig)
{
	(void)sig;
	g_exit_code = 130;
	close(STDIN_FILENO);
}

int	fork_heredoc(t_redir *redir, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		write_heredoc(redir, data);
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(redir->fd);
		waitpid(pid, &status, 0);
		return (status);
	}
}

bool	write_heredoc(t_redir *redir, t_data *data)
{
	char	*line;

	signal(SIGINT, child_sigint_handler);
	while (1)
	{
		line = readline(">");
		if (g_exit_code == 130)
		{
			close(redir->fd);
			free_data(data);
			exit(EXIT_FAILURE);
		}
		if (!line)
			break ;
		if (ft_strcmp(line, redir->delimiter) == 0)
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
	hd_file = ft_strjoin("/tmp/heredoc_", num);
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
