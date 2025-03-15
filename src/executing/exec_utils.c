// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec.utils.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/23 15:25:23 by abarahho          #+#    #+#             */
// /*   Updated: 2025/02/27 18:32:02 by abarahho         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executing.h"

int	count_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	int	i;

	current = cmds;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	**make_env(t_env *env)
{
	t_env	*current;
	char	**char_env;
	char	*tmp;
	int		i;

	current = env;
	i = 0;
	while(current)
	{
		i++;
		current = current->next;
	}
	char_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!char_env)
		return (NULL);
	current = env;
	i = 0;
	tmp = NULL;
	while (current)
	{
		tmp = join_lines(current->key, "=");
		char_env[i] = join_lines(tmp, current->value);
		free(tmp);
		i++;
		current = current->next;
	}
	char_env[i] = NULL;
	return (char_env);
}

void	free_paths(char **paths, char *path)
{
	if (paths)
		free_strs(paths);
	if (path)
		free(path);
}

bool	is_builtins(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

void	close_all_pipes(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->fd[0] >= 0)
			close(current->fd[0]);
		if (current->fd[1] >= 0)
			close(current->fd[1]);
		printf("\nvalue :%s\npipe[0]%d\npipe[1]%d\n\n", current->cmd[0], current->fd[0], current->fd[1]);
		current = current->next;
	}
}

void	close_pipes(t_cmd *cmd)
{
	if (cmd->fd[0] >= 0)
			close(cmd->fd[0]);
	if (cmd->fd[1] >= 0)
		close(cmd->fd[1]);
	printf("\nclose pipes\nvalue :%s\npipe[0]%d\npipe[1]%d\n\n", cmd->cmd[0], cmd->fd[0], cmd->fd[1]);
}
