/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:44 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/13 19:12:00 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void	ft_echo(char *str, t_env env, bool option_n)
{
	int		i;

	i = -1;
	(void)env;
	while (str[++i])
		write(1, &str[i], 1);
	if (!option_n)
		write(1, "\n", 1);
}
