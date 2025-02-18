/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:23:37 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 10:42:10 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*destination;
	char	*source;
	size_t	i;

	destination = (char *)dest;
	source = (char *)src;
	i = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (destination);
}

// int main(int argc, char *argv[])
// {
// 	char *src = argv[1];
// 	size_t n = (size_t)atoi(argv[2]);
// 	char *dest = malloc((n + 1) * sizeof(char));
// 	memset(dest, 0, n + 1);
// 	ft_memcpy(dest, src, n);
// 	printf("Source: \"%s\"\n", src);
// 	printf("Destination after memcpy: \"%s\"\n", dest);
// 	return (0);
// }