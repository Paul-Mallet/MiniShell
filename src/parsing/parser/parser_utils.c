/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:38:47 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/15 15:25:55 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

void	print_token(t_token *token)
{
	while (token)
	{
		printf("Type: %d\n", token->type);
		printf("Value: %s\n", token->value);
		token = token->next;
	}
}

int is_redirection(char c)
{
	return (c == '<' || c == '>');
}

int is_pipe(char c)
{
	return (c == '|');
}

size_t get_word_length(char *str)
{
	size_t len;

	len = 0;
	while (str[len] && !is_redirection(str[len]) && !is_pipe(str[len]) && str[len] != ' ')
		len++;
	return (len);
}

char *extract_word(char *str, size_t len)
{
	char *word;
	size_t i;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}