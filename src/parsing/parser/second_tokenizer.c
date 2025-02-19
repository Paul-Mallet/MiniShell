/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:09:37 by paul_mallet       #+#    #+#             */
/*   Updated: 2025/02/19 17:26:28 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

#define UNKNOWN_SUBTYPE -1


void handle_token_redir(t_token *token)
{
	if (!ft_strcmp(token->value, ">>"))
		token->subtype = APPEND;
	else if (!ft_strcmp(token->value, "<<"))
		token->subtype = HEREDOC;
	else if (token->value[0] == '<') //test<test
		token->subtype = REDIR_INPUT;
	else if (token->value[0] == '>')
		token->subtype = REDIR_OUTPUT;
}

void	handle_token_word(t_token *current, char **paths, bool *is_cmd_found)
{
	// if (current->prev->subtype == HEREDOC
	// 	|| current->prev->prev->subtype == HEREDOC)
	// 	current->subtype = DELIM;
	if (is_cmd(paths, current->value) && *is_cmd_found == false)
	{
		current->subtype = CMD;
		*is_cmd_found = true;
	}
	else if (is_file(current->value) == 1)
		current->subtype = FILES;
	else if (is_dir(current->value) == 1)
		current->subtype = DIR;
	else
		current->subtype = ARG;
}


void second_tokenization(t_token *tokens, t_env *env)
{
	char	**paths;
	t_token	*current;
	bool	is_cmd_found;

	paths = get_path_vrbl(env);
	current = tokens;
	is_cmd_found = false;
	// if (!paths) error_handling();
	while (current)
	{
		if (current->type == PIPE)
		{
			current->subtype = IS_PIPE;
			is_cmd_found = false;
		}
		else if (current->type == SEPARATOR)
			current->subtype = IS_SEPARATOR;
		else if (current->type == REDIR && current->value)
			handle_token_redir(current);
		else if (current->type == WORD && current->value)
			handle_token_word(current, paths, &is_cmd_found);
			// handle_token_word(current, paths);
		current = current->next;
	}
	free_paths(paths);
}
