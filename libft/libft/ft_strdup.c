/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:25:10 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 10:42:49 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	size;
	char	*dup;

	i = 0;
	size = ft_strlen(s);
	dup = malloc((size + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (i < size)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// int	main(int ac, char **av)
// {
// 	int		i;
// 	char	*dup;

// 	i = 1;
// 	while (i < ac)
// 	{
// 		dup = ft_strdup(av[i]);
// 		if (dup != NULL)
// 		{
// 			printf("Source : %s\nDuplication : %s\n", av[i], dup);
// 			free (dup);
// 		}
// 		i++;
// 	}
// }