/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:22:36 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 18:35:38 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(int fd, char c)
{
	if (fd < 0)
	{
		ft_dprintf(2, "Invalid file descriptor: %d\n", fd);
		return (-1);
	}
	if (write(fd, &c, 1) == -1)
	{
		perror("write error in print_c");
		return (-1);
	}
	return (1);
}
