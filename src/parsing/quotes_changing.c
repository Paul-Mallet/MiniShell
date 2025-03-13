/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_changing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:03:11 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/12 18:06:53 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

int	count_ins_quotes(char *value, int *i, char c)
{
	int	len;

	len = 0;
	*i += 1;
	while (value[*i] && value[*i] != c)
	{
		len++;
		*i += 1;
	}
	if (value[*i] == c)
		*i += 1;
	return (len);
}

int	len_without_qtes(char *value, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == c)
			len += count_ins_quotes(value, &i, c);
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

void	fill_without_quotes(char *dest, char *src, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == c)
		{
			i++;
			while(src[i] && src[i] != c)
				dest[j++] = src[i++];
			if (src[i] == c)
				i++;
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
}