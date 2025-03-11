/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:36 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/11 19:02:45 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

void	get_expanded(t_token *tokens, t_env *env)
{
	t_token	*current;
	char	*expansion;

	current = tokens;
	expansion = NULL;
	while (current)
	{
		if (current->type == WORD && current->subtype != DELIM)
		{
			expansion = expander(current->value, env);
			if (expansion && ft_strcmp(expansion, current->value))
			{
				free(current->value);
				current->value = expansion;
			}
			free(current->value);
			current->value = expansion;
		}
		current = current->next;
	}
}

int	count_ins_quotes(char **value)
{
	int	len;

	len = 0;
	(*value)++;
	while (**value && **value != '"')
	{
		len++;
		(*value)++;
	}
	if (**value == '"')
		(*value)++;
	return (len);
}

int	len_without_dble_qtes(char *value)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '"')
			len += count_ins_quotes(&value);
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

void	fill_without_quotes(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '"')
		{
			i++;
			while(src[i] && src[i] != '"')
				dest[j++] = src[i++];
			if (src[i] == '"')
				i++;
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
}

void	remove_join_double_quotes(t_token *tokens)
{
	char	*new_value;
	int		len;

	if (!tokens || !tokens->value)
		return ;
	len = len_without_dble_qtes(tokens->value);
	new_value = malloc((len + 1) * sizeof(char));
	if (!new_value)
		return ;
	fill_without_quotes(new_value, tokens->value);
	free(tokens->value);
	tokens->value = NULL;
	tokens->value = new_value;
}

void	remove_double_quotes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current && current->type == WORD)
		{
			if (if_double_quotes(current->value))
				remove_join_double_quotes(current);
		}
		current = current->next;
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
	print_token(data->tokens);
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
