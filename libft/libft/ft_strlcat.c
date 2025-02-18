/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:30:48 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 10:42:56 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	free_space;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	free_space = size - dst_len - 1;
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] && i < free_space)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// int	main(void)
// {
// 	char		dest[20] = "Hello";
// 	const char	*src = " World!";
// 	size_t	size = 15;
// 	size_t	result = ft_strlcat(dest, src, size);
// 	printf("String after function : %s\n", dest);
// 	printf("Total length after function : %zu\n", result);
// 	return (0);
// }