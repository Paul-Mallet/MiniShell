/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:44:59 by abarahho          #+#    #+#             */
/*   Updated: 2024/11/01 12:24:58 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s))
	{
		res = (char *)malloc(1 * sizeof(char));
		if (res == NULL)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

// int	main(int ac, char **av)
// {
// 	int				i;
// 	char			*res;
// 	unsigned int	start;
// 	size_t			len;
// 	start = (unsigned int)ft_atoi(av[2]);
// 	len = (size_t)ft_atoi(av[3]);
// 	res = ft_substr(av[1], start, len);
// 	printf("Source : %s\nSous-chaine : %s\n", av[1], res);
// 	free (res);
//	return (0):
//	}
