/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:22:43 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 18:35:38 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_x(int fd, unsigned long n)
{
	static int	count;

	count = 0;
	if (n >= 16)
		print_x(fd, n / 16);
	print_c(fd, "0123456789abcdef"[n % 16]);
	count++;
	return (count);
}

int	print_p(int fd, void *ptr)
{
	int		res;
	long	address;

	res = 0;
	address = (long)ptr;
	if (ptr == NULL)
		return (print_s(fd, "(nil)"));
	res += print_s(fd, "0x");
	res += print_x(fd, address);
	return (res);
}
