/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:28:40 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/14 17:44:44 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

void  ft_lexer(char *input)
{
	/*
		* empty, only spaces, display nothing
		* quotes(sub functions)
		*   single & dble amount
		*     odd = error
		*     even = ignore 1 inside, except empty outside the marks
		* wrong pipes
		* wrong redir
		* cmd not found
	*/
	if (ft_isempty(input) || ft_isspaces(input))
		return ;
	if (!ft_valid_quotes(input))
		//error msg + exit
	if (!ft_valid_pipes(input))
		//error msg + exit
	if (!ft_valid_redir(input))
		//error_msg + exit
}
