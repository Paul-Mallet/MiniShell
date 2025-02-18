/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:21:56 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 10:42:51 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// char	f(unsigned int i, char c)
// {
// 	(void)i;
// 	if (*c == 'a')
// 		*c = 'o';
// }

// int	main(void)
// {
// 	char	*str;

// 	str = "banana";
// 	printf("Before : %s\n", str);
// 	ft_striteri(str, f);
// 	printf("After : %s\n", str);

// 	return (0);
// }