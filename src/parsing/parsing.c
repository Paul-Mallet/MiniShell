/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/24 13:09:30 by abarahho         ###   ########.fr       */
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

int	strlen_without_quotes(char *value)
{
	int	len;

	len = 0;
	while (*value)
	{
		if (*value == '\"')
		{
			value++;
			while (*value != '\"' && *value)
			{
				value++;
				len++;
			}
			if (*value == '\"')
				value++;
		}
		else if (*value == '\'')
		{
			value++;
			while (*value != '\'' && *value)
			{
				value++;
				len++;
			}
			if (*value == '\'')
				value++;
		}
		else
		{
			value++;
			len++;
		}
	}
	return (len);
}

void	remove_join_quotes(t_token *tokens)
{
	char			*str;
	int				i;
	int				j;

	str = (char *)malloc((strlen_without_quotes(tokens->value) + 1) * sizeof(char));
	if (!str)
		return ;
	i = 0;
	j = 0;
	while (tokens->value[i])
	{
		if (tokens->value[i] == '\"')
		{
			i++;
			while (tokens->value[i] != '\"' && tokens->value[i])
				str[j++] = tokens->value[i++];
			if (tokens->value[i] == '\"')
				i++;
		}
		else if (tokens->value[i] == '\'')
		{
			i++;
			while (tokens->value[i] != '\'' && tokens->value[i])
				str[j++] = tokens->value[i++];
			if (tokens->value[i] == '\'')
				i++;
		}
		else
			str[j++] = tokens->value[i++];
	}
	str[strlen_without_quotes(tokens->value)] = '\0';
	free(tokens->value);
	tokens->value = str;
}

void	remove_tokens_join_quotes(t_token *tokens)
{
	// printf("bef: \n\n\n%s\n\n\n\n", tokens->value);
	while (tokens)
	{
		printf("\n\n\n%s, %d\n\n\n\n", tokens->value, tokens->type);
		if (tokens && tokens->type == WORD)
			remove_join_quotes(tokens);
		tokens = tokens->next;
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

void	remove_empty_token(t_token **tokens)
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

t_token	*ft_parsing(char *value, t_env *env)
{
	char	*trimmed;
	t_token	*tokens;

	(void)env;
	trimmed = ft_strtrim(value, " \t\n");
	tokens = first_tokenization(trimmed);
	free(trimmed);
	remove_empty_token(&tokens);
	join_tokens(&tokens);
	remove_tokens_join_quotes(tokens); //e''cho doesn't work
	second_tokenization(tokens, env);
	get_expanded(tokens, env);
	if (!check_cmd_tokens(tokens))
	{
		free_tokens(&tokens);
		return (NULL);
	}
	return (tokens);
}