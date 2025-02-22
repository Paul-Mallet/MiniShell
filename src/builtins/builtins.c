/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:46:29 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/22 18:04:38 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

/*
	builtins conditions
	1. input is already parsed(trim, cmds, args validation)
	2. check input fit builtins names(strcmp)
	3. send input without builtins(strchr + 1, skip ' ')
*/

void	ft_builtins(t_data *data) // builtins doivent retourner un int pour verifier exit error;
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (current->subtype == CMD)
		{
			if (!ft_strcmp(current->value, "echo"))
				ft_echo(current);
			// if (!ft_strncmp(input, "cd", 2))
			// 	ft_cd(ft_strchr(input, ' ') + 1);
			if (!ft_strcmp(current->value, "pwd"))
				ft_pwd();
			// if (!ft_strcmp(input, "export"))
			// 	ft_export(input, &data->env);
			// if (!ft_strcmp(current->value, "unset"))
			// 	ft_unset(data->env);
			if (!ft_strcmp(current->value, "env"))
				ft_env(data->env);
			// if (!ft_strcmp(input, "exit"))
			// 	ft_exit(data, input, prompt);
		}
		current = current->next;	
	} 
}