/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:10 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/20 15:12:47 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include "../../includes/parsing.h"

void	ft_exit(t_data *data, char *input, char *prompt)
{
	free(prompt);
	if (data)
	{
		free(input);
		free_env(&data->env);
		free_tokens(&data->tokens);
	}
	exit(data->exit_code);
}
