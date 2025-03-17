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

static char	**malloc_char_env(t_env *env)
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
	return (char_env);
}

char	**make_env(t_env *env)
{
	t_env	*current;
	char	**char_env;
	char	*tmp;
	int		i;

	char_env = malloc_char_env(env);
	if (!char_env)
		return (NULL);
	tmp = NULL;
	i = 0;
	current = env;
	while (current)
	{
		tmp = ft_strjoin(current->key, "=");
		char_env[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		i++;
		current = current->next;
	}
	char_env[i] = NULL;
	return (char_env);
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
		close_pipes(current);
		current = current->next;
	}
}

void	close_pipes(t_cmd *cmd)
{
	if (cmd->fd[0] >= 0)
			close(cmd->fd[0]);
	if (cmd->fd[1] >= 0)
		close(cmd->fd[1]);
}
