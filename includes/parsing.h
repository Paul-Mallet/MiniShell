/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:43:05 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/15 10:47:03 by paul_mallet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "./minishell.h"

/*
	* trim 1rst & last spaces
	* reduce spaces between each word to 1
*/
char	*ft_parsing(char *input);

void  	ft_lexer(char *input);

/*
	fonctions pour la liste chainee
*/
t_token	*new_token(t_token_first type, char *value);
void	token_add_back(t_token **lst, t_token *new);
void	free_token(t_token **token);


#endif
