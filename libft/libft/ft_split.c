/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:00:01 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 10:42:34 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

int	free_array(char **array, size_t j)
{
	long	i;

	i = j - 1;
	if (array[i] == NULL)
	{
		i--;
		while (i >= 0)
		{
			free(array[i]);
			i--;
		}
		free(array);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**array;

	array = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = -1;
	j = 0;
	index = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			array[j++] = word_dup(s, index, i);
			index = -1;
			if (free_array(array, j) == 1)
				return (NULL);
		}
	}
	array[j] = NULL;
	return (array);
}

// int	main(int argc, char **argv)
// {
// 	char	**result;
// 	int		i;
// 	result = ft_split(argv[1], argv[2][0]);
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);
// 	return (0);
// }