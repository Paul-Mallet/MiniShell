/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:44:18 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/06 13:38:08 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

bool	is_dollar(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

void	remove_token(t_token *token)
{
	if (token->prev && token->next)
	{
		token->prev->next = token->next;
		token->next->prev = token->prev;
	}
	else if (token->prev && !token->next)
		token->prev->next = NULL;
	else if (!token->prev && token->next)
		token->next->prev = NULL;
	free(token);
}

void	remove_empty_token(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (!ft_strcmp(current->value, "\"\"") || !ft_strcmp(current->value, "''"))
		{
			free (current->value);
			current->value = strdup("");
		}
		current = current->next;
	}
}

void	join_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;
	char	*tmp_value;

	tmp_value = NULL;
	current = *tokens;
	while (current && current->next)
	{
		next = current->next;
		if (current->type == WORD && next->type == WORD)
		{
			if (is_dollar(current->value))
			{
				current = next;
				continue ;
			}
			tmp_value = ft_strdup(current->value);
			free(current->value);
			next->value = ft_strjoin(tmp_value, next->value);
			free(tmp_value);
			if (current == *tokens)
				*tokens = next;
			remove_token(current);
		}
		current = next;
	}
}

int	check_cmd_tokens(t_token *tokens)
{
	t_token	*current;
	bool	cmd_expected;

	current = tokens;
	cmd_expected = true;
	while (current)
	{
		if (cmd_expected)
		{
			if (current->subtype == CMD)
				cmd_expected = false;
			else if (current->subtype != IS_SEPARATOR)
			{
				return (0);
			}
		}
		if (current->subtype == IS_PIPE)
			cmd_expected = true;
		current = current->next;
	}
	return (1);
}
