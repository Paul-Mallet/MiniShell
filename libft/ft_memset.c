/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:07:23 by abarahho          #+#    #+#             */
/*   Updated: 2024/11/01 15:33:45 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int value, size_t count)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < count)
	{
		ptr[i] = (char)value;
		i++;
	}
	return (ptr);
}

// int	main(void)
// {
// 	char	array[20];
// 	int		i;
// 	i = 0;
// 	printf("%s", array);
// 	ft_memset(array, 'a', sizeof(array));
// 	while (i < sizeof(array))
// 	{
// 		printf("%c", array[i]);
// 		i++;
// 	}
// 	return (0);
// }