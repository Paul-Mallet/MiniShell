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
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

char	**make_env(t_env *env)
{
	t_env	*current;
	char	**char_env;
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
	while (current)
	{
		char_env[i] = join_lines(current->key, "=");
		char_env[i] = join_lines(char_env[i], current->value);
		i++;
		current = current->next;
	}
	char_env[i] = NULL;
	return (char_env);
}

void free_paths(char **paths, char *path)
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
		if (cmd->fd[0] != -1)
			close(cmd->fd[0]);
		if (cmd->fd[1] != -1)
			close(cmd->fd[1]);
}
