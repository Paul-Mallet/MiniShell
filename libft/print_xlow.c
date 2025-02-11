/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xlow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:22:51 by abarahho          #+#    #+#             */
/*   Updated: 2025/01/14 13:49:13 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_xlow(int fd, unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += print_xlow(fd, n / 16);
	print_c(fd, "0123456789abcdef"[n % 16]);
	count++;
	return (count);
}
