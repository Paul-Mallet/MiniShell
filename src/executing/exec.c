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

#include "../../includes/minishell.h"
#include "../../includes/executing.h"
#include "../../includes/signals.h"

void	exec(t_data *data)
{
	int		nb_cmd;
	char	**envp;

	(void)nb_cmd;
	// (void)envp;
	// (void)data;
	envp = make_env(data->env);
	// int i = 0;
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	

	check_heredoc(data);	// ft_builtins(data);
	// nb_cmd = count_cmds(data->cmds);
	// exec_command(data, envp);
	// free_strs(envp);
}



int	exec_command(t_data *data, char **envp)
{
	pid_t	pid;
	char	*path;

	path = find_path(envp, data->cmds->cmd[0]);
	if (!path)
	{
		perror("find_path");
		return (EXIT_FAILURE);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); //ctrl + C (^C + new line)
		signal(SIGQUIT, SIG_DFL); //ctrl + \ (core dump)
		redir_managing(data);
		execve(path, data->cmds->cmd, envp);
		perror("execve");
		free(path);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &data->exit_code, 0);
	free(path);
	return (1);
}




