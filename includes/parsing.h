/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:43:05 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/17 14:23:56 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "./minishell.h"

/*
	expander
*/
char	*expander(char *input, t_env *env);
char	*expand_single_var(char *input, int i, t_env *env);
char	*get_env_value(int end, int start, char *input, t_env *env);
char	*replace_var(char *input, int start, int end, char *value);

/*
	lexer checks if input is valid
*/
void  	ft_lexer(char *input);

/*
	parsing correctly formats input before tokenize it
	* trim 1rst & last spaces
	* reduce spaces between each word to 1
*/
t_token	*ft_parsing(char *input);

/*
	1rst tokenizer separates words of input by types
*/
t_token	*new_token(t_token_first type, char *value);
void	token_add_back(t_token **lst, t_token *new);
t_token	*first_tokenization(char *input);
void	print_token(t_token *token);
void 	free_token(t_token **tokens);


t_token	*handle_word(char **input);
t_token *handle_quotes(char **input);
t_token	*handle_pipe(char **input);
t_token	*handle_redirection(char **input);

char	*extract_word(char *str, size_t len);

size_t	get_word_length(char *str);
size_t	get_quotes_length(char *str);

int		is_pipe(char c);
int		is_redirection(char c);

/*
	2nd tokenizer separates types of input by subtypes
*/
int ft_is_all_alnum(char *str);

#endif
