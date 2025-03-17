/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:03:54 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 18:35:38 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_prcssformat(char format, va_list args, int fd)
{
	if (format == 'c')
		return (print_c(fd, va_arg(args, int)));
	else if (format == 's')
		return (print_s(fd, va_arg(args, char *)));
	else if (format == 'p')
		return (print_p(fd, va_arg(args, void *)));
	else if (format == 'd')
		return (print_nbr(fd, va_arg(args, int)));
	else if (format == 'i')
		return (print_nbr(fd, va_arg(args, int)));
	else if (format == 'u')
		return (print_u(fd, va_arg(args, unsigned int)));
	else if (format == 'x')
		return (print_xlow(fd, va_arg(args, unsigned int)));
	else if (format == 'X')
		return (print_xup(fd, va_arg(args, unsigned int)));
	else if (format == '%')
		return (print_c(fd, '%'));
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	count = 0;
	i = 0;
	va_start (args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			count += ft_prcssformat(format[i], args, 1);
		}
		else
		{
			print_c(1, format[i]);
			count++;
		}
		i++;
	}
	va_end (args);
	return (count);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	count = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			count += ft_prcssformat(format[i], args, fd);
		}
		else
		{
			print_c(fd, format[i]);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
