/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:10:45 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/12 14:12:24 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

int	len_without_sgle_qtes(char *value)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
		{
			i++;
			while (value[i] && value[i] != '\'' )
			{
				i++;
				len++;
			}
			if (value[i] && value[i] == '\'')
				i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

void	remove_join_sgle_quotes(t_token *tokens)
{
	char	*str;
	int		i;
	int		j;
	t_token	*current;		

	str = malloc((len_without_sgle_qtes(tokens->value) + 1) * sizeof(char));
	if (!str)
		return ;
	i = 0;
	j = 0;
	current = tokens;
	while (current->value[i])
	{
		if (current->value[i] == '\'')
		{
			i++;
			while (current->value[i] != '\'' && current->value[i])
				str[j++] = current->value[i++];
			if (current->value[i] == '\'')
				i++;
		}
		else
			str[j++] = current->value[i++];
	}
	str[len_without_sgle_qtes(current->value)] = '\0';
	free(current->value);
	current->value = str;
}

void	remove_single_quotes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current && current->type == WORD)
		{
			if (if_single_quotes(current->value))
				remove_join_sgle_quotes(current);
		}
		current = current->next;
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

bool	if_single_quotes(char *value)
{
	int	i;

	i = 0;
	while(value[i])
	{
		if (value[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}
