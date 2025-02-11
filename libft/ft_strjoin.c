/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:12:24 by abarahho          #+#    #+#             */
/*   Updated: 2024/11/03 13:54:01 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t		total_len;
	char		*res;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (total_len + 1));
	if (res == NULL)
		return (NULL);
	*res = '\0';
	ft_strlcat(res, s1, total_len + 1);
	ft_strlcat(res, s2, total_len + 1);
	return (res);
}

// int	main(int ac, char **av)
// {
// 	char	*res;
// 	res = ft_strjoin(av[1], av[2]);
// 	printf("%s\n", res);
// 	return (0);
// }
