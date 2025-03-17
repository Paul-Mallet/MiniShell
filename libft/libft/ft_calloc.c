/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:07:47 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 18:35:38 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	len;
	void	*ptr;

	len = nmemb * size;
	ptr = malloc(len);
	if (ptr == NULL)
		return (NULL);
	ft_bzero (ptr, len);
	return (ptr);
}

// int main(int ac, char **av)
// {
// 	size_t	i;
// 	size_t	nmemb;
// 	size_t	size;
// 	int		*array;
// 	i = 0;
// 	nmemb = (size_t)atoi(argv[1]);
// 	size = (size_t)atoi(argv[2]);
// 	array = (int *)ft_calloc(nmemb, size);
// 	while (i < nmemb)
// 	{
// 		printf("array[%zu] = %d\n", i, array[i]);
// 		i++;
// 	}
// 	free(array);
// 	return (0);
// }
