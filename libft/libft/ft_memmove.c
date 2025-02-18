/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:27:14 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 10:42:15 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if ((dest > src) && (dest < src + n))
	{
		while (n > 0)
		{
			n--;
			((unsigned char *)dest)[n] = ((const unsigned char *)src)[n];
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

// int main(int ac, char **av)
// {
// 	char	*src = av[1];
// 	int		offset = atoi(av[2]);
// 	size_t n = (size_t)atoi(av[3]);
// 	size_t buffer_size = strlen(src) + offset + 1;
// 	char *buffer = malloc(buffer_size);
// 	strcpy(buffer, src);
// 	char *dest = buffer + offset;
// 	printf("Before ft_memmove:\n");
// 	printf("Source : %s\n", buffer);
// 	printf("Dest   : %s\n", dest);
// 	ft_memmove(dest, buffer, n);
// 	printf("\nAfter ft_memmove:\n");
// 	printf("Source : %s\n", buffer);
// 	printf("Dest   : %s\n", dest);
// 	return (0);
// }