/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:25:02 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 18:35:38 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*src;
	size_t	i;

	src = (char *)s;
	i = 0;
	while (i < n)
	{
		if (src[i] == (char)c)
			return (&src[i]);
		i++;
	}
	return (NULL);
}

// int main(int ac, char **av)
// {
//     size_t len;
//     char *result;
// 	char *rslt;
// 	len = strlen(av[1]);
// 	rslt = (char *)memchr(av[1], av[2][0], len);
// 	result = (char *)ft_memchr(av[1], av[2][0], len);
// 	printf("My function : '%c' found character : %s\n", av[2][0], result);
// 	printf("The memchr funcion : '%c' found character : %s\n", av[2][0], rslt);
//     return 0;
// }