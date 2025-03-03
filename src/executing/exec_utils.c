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
				if (!redir_heredoc(current_redir))
					data->exit_code = 0;
			}
			current_redir = current_redir->next;
		}
		current = current->next;
	}
}

char	**make_env(t_env *env)
{
	t_env	*current;
	char	**envp;
	int		i;

	current = env;
	i = 0;
	while(current)
	{
		i++;
		current = current->next;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		envp[i] = join_lines(current->key, "=");
		envp[i] = join_lines(envp[i], current->value);
		i++;
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}
