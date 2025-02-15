/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:43:05 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/14 19:28:59 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "./minishell.h"

t_token	*init_tokens(char *input);
t_token	*handle_word(char **input);
t_token	*handle_pipe(char **input);
t_token	*handle_redirection(char **input);
char	*extract_word(char *str, size_t len);
size_t	get_word_length(char *str);
int		is_pipe(char c);
int		is_redirection(char c);
void	print_token(t_token *token);

/*
	fonctions pour la liste chainee
*/
t_token	*new_token(t_token_first type, char *value);
void	token_add_back(t_token **lst, t_token *new);
void	free_token(t_token **token);


#endif
