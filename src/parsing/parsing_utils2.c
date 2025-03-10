/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:10:45 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/10 18:23:52 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

int	len_without_sgle_qtes(char *value)
{
	int	len;

	len = 0;
	while (*value)
	{
		if (*value == '\'')
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

void	remove_join_sgle_quotes(t_token *tokens)
{
	char			*str;
	int				i;
	int				j;

	str = malloc((len_without_sgle_qtes(tokens->value) + 1) * sizeof(char));
	if (!str)
		return ;
	i = 0;
	j = 0;
	while (tokens->value[i])
	{
		if (tokens->value[i] == '\'')
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
	str[len_without_sgle_qtes(tokens->value)] = '\0';
	free(tokens->value);
	tokens->value = str;
}

void	remove_single_quotes(t_token *tokens)
{
	while (tokens)
	{
		if (tokens && tokens->type == WORD)
			remove_join_sgle_quotes(tokens);
		tokens = tokens->next;
	}
}

bool	if_double_quotes(char *value)
{
	int	i;

	i = 0;
	while(value[i])
	{
		if (value[i] == '"')
			return (true);
		i++;
	}
	return (false);
}
