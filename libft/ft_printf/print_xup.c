/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:22:54 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/18 10:57:36 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	print_xup(int fd, unsigned int n)
{
	static int	count;

	count = 0;
	if (n >= 16)
		print_xup(fd, n / 16);
	print_c(fd, "0123456789ABCDEF"[n % 16]);
	count++;
	return (count);
}
