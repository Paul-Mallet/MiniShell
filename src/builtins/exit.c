/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:10 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/13 10:14:02 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"
#include "../../includes/parsing.h"

void	ft_exit(t_data *data)
{
	printf("\nexit\n");
	if (data)
	{
		free(data->input);
		free(data->prompt);
		free_env(&data->env);
		free_cmd_struct(&data->cmds);
		free_tokens(&data->tokens);
	}
	exit((unsigned char)data->exit_code % 256);
}
