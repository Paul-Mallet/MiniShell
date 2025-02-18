/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:09:37 by paul_mallet       #+#    #+#             */
/*   Updated: 2025/02/18 17:08:38 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		paths[i] = NULL;
		i++;
	}
	free (paths);
}

// static int	ft_token_size(t_token *current)
// {
// 	int	i;

// 	i = 0;
// 	while (current != NULL)
// 	{
// 		i++;
// 		current = current->next;
// 	}
// 	return (i);
// }

void second_tokenization(t_token *tokens, t_env *env)
{
	char	**paths;
	t_token	*current;

	current = tokens;
	paths = get_path_vrbl(env);
	while (current)
	{
		if (current->type == REDIR && current->value)
		{
			if (!ft_strcmp(current->value, ">>"))
				current->subtype = APPEND;
			else if (!ft_strcmp(current->value, "<<"))
				current->subtype = HEREDOC;
			else if (current->value[0] == '>')
				current->subtype = REDIR_INPUT;
			else if (current->value[0] == '<')
				current->subtype = REDIR_OUTPUT;
		}
		else if (current->type == WORD && current->value) //word1 word2
		{
			if (current->prev && current->prev->subtype == HEREDOC)
				current->subtype = DELIM;
			else if (is_cmd(paths, current->value))
				current->subtype = CMD;
			else if (current->prev && current->prev->type == SEPARATOR
				&& current->prev->prev && current->prev->prev->subtype == CMD
				&& current->value[0] == '-')
				current->subtype = ARG;
			else if (current->prev && current->prev->value[0] == '>')
				current->subtype = FILES;
			else if (current->next && current->next->value[0] == '<')
				current->subtype = FILES;
			// else if (current->next->value[0] == '<' && current->next)
			// 	current->subtype = FILES;
		}
		else if (current->type == PIPE || current->type == SEPARATOR)
				current->subtype = -1;
		else
			current->subtype = 666;
		current = current->next;
	}
	if (paths)
		free_paths(paths);
}
