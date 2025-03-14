/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:09:37 by paul_mallet       #+#    #+#             */
/*   Updated: 2025/03/12 15:43:03 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"
#include "../../../includes/executing.h"

#define UNKNOWN_SUBTYPE -1

void	handle_token_redir(t_token *token)
{
	if (!ft_strcmp(token->value, ">>"))
		token->subtype = APPEND;
	else if (!ft_strcmp(token->value, "<<"))
		token->subtype = HEREDOC;
	else if (token->value[0] == '<')
		token->subtype = REDIR_INPUT;
	else if (token->value[0] == '>')
		token->subtype = REDIR_OUTPUT;
}

void	handle_token_word(t_token *current, char **paths, bool *is_cmd_found, t_data *data)
{
	if ((current->prev && current->prev->subtype == HEREDOC))
		current->subtype = DELIM;
	else if ((current->prev && current->prev->subtype == IS_SEPARATOR)
		&& (current->prev->prev && current->prev->prev->subtype == HEREDOC))
		current->subtype = DELIM;
	else if ((current->prev && current->prev->type == REDIR))
		current->subtype = FILES;
	else if ((current->prev && current->prev->subtype == IS_SEPARATOR)
		&& (current->prev->prev && current->prev->prev->type == REDIR))
		current->subtype = FILES;
	else if (is_builtins(current->value) && !*is_cmd_found)
	{
		current->subtype = CMD;
		*is_cmd_found = true;
	}
	else if (is_cmd(paths, current->value, data) && !*is_cmd_found)
	{
		current->subtype = CMD;
		*is_cmd_found = true;
	}
	else
		current->subtype = ARG;
}

void	second_tokenization(t_data *data)
{
	t_token	*current;
	char	**paths;
	bool	is_cmd_found;

	paths = get_path_vrbl(data->env);
	current = data->tokens;
	is_cmd_found = false;
	while (current)
	{
		if (current->type == PIPE)
		{
			current->subtype = IS_PIPE;
			is_cmd_found = false;
		}
		else if (current->type == REDIR)
			handle_token_redir(current);
		else if (current->type == SEPARATOR)
			current->subtype = IS_SEPARATOR;
		else if (current->type == WORD)
			handle_token_word(current, paths, &is_cmd_found, data);
		current = current->next;
	}
	free_strs(paths);
}
