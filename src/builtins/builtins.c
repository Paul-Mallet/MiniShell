/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:46:29 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/24 17:32:46 by abarahho         ###   ########.fr       */
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
			if (!ft_strcmp(current->value, "cd"))
				ft_cd(current->next->next->value);
			if (!ft_strcmp(current->value, "pwd"))
				ft_pwd();
			// if (!ft_strcmp(current->value, "export"))
			// 	ft_export(data->tokens, data->env);
			if (!ft_strcmp(current->value, "unset"))
				ft_unset(&data->env, current);
			if (!ft_strcmp(current->value, "env"))
				ft_env(data->env);
			// if (!ft_strcmp(input, "exit"))
			// 	ft_exit(data, input, prompt);
		}
		current = current->next;	
	} 
}
