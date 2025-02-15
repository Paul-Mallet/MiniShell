/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:43:05 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/15 11:33:19 by paul_mallet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "./minishell.h"

/*
	lexer checks if input is valid
*/
void  	ft_lexer(char *input);

/*
	parsing correctly formats input before tokenize it
	* trim 1rst & last spaces
	* reduce spaces between each word to 1
*/
char	*ft_parsing(char *input);

/*
	tokenizer separates each word of input by type
*/
t_token	*init_tokens(char *input);
t_token	*handle_word(char **input);
t_token	*handle_pipe(char **input);
t_token	*handle_redirection(char **input);
char	*extract_word(char *str, size_t len);
size_t	get_word_length(char *str);
int		is_pipe(char c);
int		is_redirection(char c);
void	print_token(t_token *token);

// t_token	*new_token(t_token_first type, char *value);
// void	token_add_back(t_token **lst, t_token *new);
// void	free_token(t_token **token);

#endif
