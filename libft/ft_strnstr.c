/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:52:23 by abarahho          #+#    #+#             */
/*   Updated: 2024/11/01 12:58:06 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && (i < len))
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (little[j] && (i + j) < len
				&& big[i + j] && big[i + j] == little[j])
				j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

// int	main(int ac, char **av)
// {
// 	printf("My function : %s\n", ft_strnstr(av[1], av[2], atoi(av[3])));
// 	return (0);
// }