/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/20 12:09:34 by paul_mallet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	get_expanded(t_token *tokens, t_data *data)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->subtype == ARG || current->subtype == FILES)
			current->value = expander(current->value, data);
		current = current->next;
	}
}

void	quoteless(char *token)
{
	int		j;
	int		i;
	bool	in_single;
	bool	in_double;

	i = 0;
	j = 0;
	in_single = false;
	in_double = false;
	while (token[i])
	{
		if (!in_single && token[i] == '\"')
			in_double = !in_double;
		else if (!in_double && token[i] == '\'')
			in_single = !in_single;
		else if ((in_single && token[i] != '\'')
			|| (in_double && token[i] != '\"')
			|| (!in_double && !in_single))
		{
			token[j] = token[i];
			j++;
		}
		i++;
	}
	token[j] = 0;
}

void	remove_quotes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == WORD)
			quoteless(current->value);
		current = current->next;
	}
}

static bool	check_whitespace(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while(current)
	{
		if (current->type == REDIR)
			return (true);
		if (current->subtype == ARG && !ft_isspaces(current->value))
			return (true);
		current = current->next;
	}
	return (false);
}

bool	check_tokens (t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (!current->next && current->type != WORD)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", current->value);
			return (false);
		}
		if (current->type == REDIR && current->next
			&& current->next->type != WORD && current->next->type != SEPARATOR)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (false);
		}
		if ((current->type == PIPE && current->next && current->next->type == SEPARATOR)
			|| (current->type == PIPE && current->next->next && current->next->next->type == PIPE))
		{
			printf("minishell: '%s': syntax error near unexpected token `||'\n");
			return (false);
		}
		if (ft_strcmp(current->value, "\\") == 0 || ft_strcmp(current->value, ";") == 0)
		{
			printf("minishell: '%s': not interpreted special chars\n", current->value);
			return (false);
		}
		if (current->type == PIPE && current->next && current->next->type == PIPE)
		{
			printf("minishell: '%s': not interpreted special chars\n", current->value);
			return (false);
		}
		current = current->next;
	}
	return (true);
}

bool	ft_parsing(char *value, t_data *data)
{
	char	*trimmed;

	trimmed = ft_strtrim(value, " \t\n");
	data->tokens = first_tokenization(trimmed);
	free(trimmed);
	if (!check_tokens(data))
		return (free_parsing(data), false);
	join_tokens(&data->tokens);
	subtyping_tokens(data);
	get_expanded(data->tokens, data);
	remove_quotes(data->tokens);
	if (!check_whitespace(data->tokens))
		return (free_parsing(data), false);
	return (true);
}

