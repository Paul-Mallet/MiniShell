/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/28 16:57:28 by abarahho         ###   ########.fr       */
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

int	len_without_dble_qtes(char *value)
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
		else
		{
			value++;
			len++;
		}
	}
	return (len);
}

void	remove_join_double_quotes(t_token *tokens)
{
	char			*str;
	int				i;
	int				j;

	str = malloc((len_without_dble_qtes(tokens->value) + 1) * sizeof(char));
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
		else
			str[j++] = tokens->value[i++];
	}
	str[len_without_dble_qtes(tokens->value)] = '\0';
	free(tokens->value);
	tokens->value = str;
}

void	remove_double_quotes(t_token *tokens)
{
	while (tokens)
	{
		if (tokens && tokens->type == WORD)
			remove_join_double_quotes(tokens);
		tokens = tokens->next;
	}
}

void	ft_parsing(char *value, t_data *data)
{
	char	*trimmed;

	trimmed = ft_strtrim(value, " \t\n");
	data->tokens = first_tokenization(trimmed, data->env);
	free(trimmed);
	remove_empty_token(data->tokens);
	join_tokens(&data->tokens);
	remove_double_quotes(data->tokens);
	second_tokenization(data);
	get_expanded(data->tokens, data->env);
	remove_single_quotes(data->tokens);
	// check_cmd(data);
	// if (!check_cmd_tokens(data->tokens))
	// {
	// 	free_tokens(data->tokens);
	// 	return (NULL);
	// }
}