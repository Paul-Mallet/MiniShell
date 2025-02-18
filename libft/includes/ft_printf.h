/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:04:16 by abarahho          #+#    #+#             */
/*   Updated: 2025/01/14 13:55:09 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

int		ft_dprintf(int fd, const char *format, ...);
int		ft_printf(const char *format, ...);
int		print_c(int fd, char c);
int		print_nbr(int fd, int n);
int		print_u(int fd, unsigned int n);
int		print_p(int fd, void *ptr);
int		print_s(int fd, char *str);
int		print_xlow(int fd, unsigned int n);
int		print_xup(int fd, unsigned int n);

#endif