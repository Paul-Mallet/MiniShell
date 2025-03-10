/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:37:38 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/10 12:05:27 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

void	check_heredoc(t_data *data)
{
	t_cmd	*current;
	t_redir	*current_redir;

	current = data->cmds;
	current_redir = data->cmds->redir;
	while (current)
	{
		while (current_redir)
		{
			if (current_redir->heredoc)
			{
				if (!write_heredoc(data, current_redir))
					data->exit_code = 0;
			}
			current_redir = current_redir->next;
		}
		current = current->next;
	}
}

bool	write_heredoc(t_data *data, t_redir *redir)
{
	char	*line;
	pid_t	pid;
	int		status;

	(void)data;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); //ctrl + C (^C + new line) //IGN = ignore
		signal(SIGQUIT, SIG_DFL); //ctrl + \ (core dump)
		if (!heredoc_name(redir))
			return (false);
		while (1)
		{
			line = readline("heredoc>");
			if (!line)
			{
				printf("\nwarning: end-of-file detected (Ctrl+D)\n");
            	break;
			}
			if (ft_strcmp(line, redir->delimiter) == 0) //if !line ?
			{
				free(line);
				break ;
			}
			write(redir->fd, line, ft_strlen(line));
			write(redir->fd, "\n", 1);
			free(line);
		}
		close(redir->fd);
		free(redir->file);
		printf("end of write_heredoc\n");
		return (true);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (false);
	}
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
        return (NULL);
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
