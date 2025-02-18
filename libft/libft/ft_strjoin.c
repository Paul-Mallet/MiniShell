/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:12:24 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 10:42:53 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	i;

	i = (ft_strlen(s1) + ft_strlen(s2));
	s = (char *)malloc((i + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = (char)s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		s[ft_strlen(s1) + i] = (char)s2[i];
		i++;
	}
	s[ft_strlen(s1) + i] = '\0';
	return (s);
}

// char	*ft_strjoin(const char *s1, const char *s2)
// {
// 	size_t		total_len;
// 	char		*res;

// 	total_len = ft_strlen(s1) + ft_strlen(s2);
// 	res = malloc(sizeof(char) * (total_len + 1));
// 	if (res == NULL)
// 		return (NULL);
// 	*res = '\0';
// 	ft_strlcat(res, s1, total_len + 1);
// 	ft_strlcat(res, s2, total_len + 1);
// 	return (res);
// }

// int	main(int ac, char **av)
// {
// 	char	*res;
// 	res = ft_strjoin(av[1], av[2]);
// 	printf("%s\n", res);
// 	return (0);
// }
