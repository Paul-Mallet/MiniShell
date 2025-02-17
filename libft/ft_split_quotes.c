/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:14:50 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/17 14:10:07 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	index;
	int	count;

	i = 0;
	index = 0;
	count = 0;
	while (s[index])
	{
		if (s[index] != c && count == 0)
		{
			count = 1;
			i++;
		}
		else if (s[index] == c)
			count = 0;
		index++;
	}
	return (i);
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static char	*extract_quoted_segment(const char *s, int *i)
{
	char	quote_type;
	int		start;

	quote_type = s[*i];
	start = ++(*i);
	while (s[*i] && s[*i] != quote_type)
		(*i)++;
	if (s[*i] == quote_type)
		(*i)++;
	return (ft_substr(s, start, (*i) - start - 1));
}

static char	*extract_word(const char *s, int *i, char sep)
{
	int		start;

	start = *i;
	while (s[*i] && s[*i] != sep && !is_quote(s[*i]))
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

char	**ft_split_quotes(const char *s, char sep)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	result = malloc((count_words(s, sep) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i])
		{
			if (is_quote(s[i]))
				result[j++] = extract_quoted_segment(s, &i);
			else
				result[j++] = extract_word(s, &i, sep);
		}
	}
	result[j] = NULL;
	return (result);
}
