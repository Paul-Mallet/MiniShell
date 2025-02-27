/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/27 18:49:12 by abarahho         ###   ########.fr       */
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
	while (tokens)
	{
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

void	ft_parsing(char *value, t_data *data)
{
	char	*trimmed;

	trimmed = ft_strtrim(value, " \t\n");
	data->tokens = first_tokenization(trimmed, data->env);
	// print_token(data->tokens);
	free(trimmed);
	remove_empty_token(data->tokens);
	join_tokens(&data->tokens);
	remove_tokens_join_quotes(data->tokens); //e''cho doesn't work
	second_tokenization(data);
	get_expanded(data->tokens, data->env);
	// check_cmd(data);
	// if (!check_cmd_tokens(data->tokens))
	// {
	// 	free_tokens(data->tokens);
	// 	return (NULL);
	// }
}

// void	check_cmd(t_data *data)
// {
// 	t_token	*current;
// 	char	**paths;

// 	current = data->tokens;
// 	paths = get_path_vrbl(data->env);
// 	while (current)
// 	{
// 		if (current->subtype == ARG || current->subtype == CMD)
// 		{
// 			data->exit_code = is_cmd(paths, current->value);
// 			return ;
// 		}
// 		current = current->next;
// 	}
// 	data->exit_code = 127;
// }