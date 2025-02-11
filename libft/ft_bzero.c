/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:00:02 by abarahho          #+#    #+#             */
/*   Updated: 2024/10/31 14:38:32 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

// int	main(int ac,char **av)
// {
// 	int	i;

// 	i = 0;
// 	ft_bzero(av[1], sizeof(av[1]));
// 	while (i < sizeof(av[1]))
// 	{
// 		printf("%d", av[1][i]);
// 		i++;
// 	}
// 	return (0);
// }