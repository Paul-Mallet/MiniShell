/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/21 11:22:11 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

void	get_expanded(t_token *tokens, t_env *env)
{
	char	**paths;
	t_token	*current;
	char	*expansion;

	paths = get_path_vrbl(env);
	current = tokens;
	expansion = NULL;
	while (current)
	{
		if (current->type == WORD && current->subtype != DELIM)
		{
			expansion = expander(current->value, env);
			if (ft_strcmp(expansion, current->value))
				free(current->value);
			current->value = expansion;
		}
		current = current->next;
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
				printf("command not found %s\n", current->value);
				return (0);
			}
		}
		if (current->subtype == IS_PIPE)
			cmd_expected = true;
		current = current->next;
	}
	return (1);
}

static bool	is_dollar(char *value)
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

void	join_tokens(t_token *tokens)
{
	t_token	*current;
	char	*tmp_value;

	tmp_value = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == WORD && current->next
			&& current->next->type == WORD)
		{
			if (!is_dollar(current->value))
			{
				current = current->next;
				continue ;
			}
			tmp_value = current->value;
			free (current->value);
			current->value = ft_strjoin(tmp_value, current->next->value);
			remove_token(current->next);
		}
		current = current->next;
	}
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
	free(token->value);
	free(token);
}

static void	remove_empty_token(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	next = NULL;
	current = *tokens;
	while (current)
	{
		next = current->next;
		if (!ft_strcmp(current->value, "\"\"") || !ft_strcmp(current->value, "''"))
		{
			if (current == *tokens)
				*tokens = next;
			remove_token(current);
		}
		current = next;
	}
}
t_token	*ft_parsing(char *input, t_env *env)
{
	char	*trimmed;
	t_token	*tokens;

	(void)env;
	trimmed = ft_strtrim(input, " \t\n");
	tokens = first_tokenization(trimmed);
	free(trimmed);
	remove_empty_token(&tokens);
	join_tokens(tokens);
	second_tokenization(tokens, env);
	get_expanded(tokens, env);
	// if (!check_cmd_tokens(tokens))
	// {
	// 	free_tokens(&tokens);
	// 	return (NULL);
	// }
	return (tokens);
}