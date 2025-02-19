/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:43:05 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/19 15:12:19 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "./minishell.h"
# include "executing.h"

typedef struct	s_valid_quotes
{
	int	sgle_cnt;
	int dble_cnt;
	int	is_in_sgle;
	int	is_in_dble;
}		t_valid_quotes;

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
t_token	*ft_parsing(char *input, t_env *env);

/*
	1rst tokenizer separates words of input by types
*/
t_token	*new_token(t_token_first type, t_token_scnd subtype, char *value);
void	token_add_back(t_token **lst, t_token *new);
t_token	*first_tokenization(char *input);
void	second_tokenization(t_token *tokens, t_env *env);
void	print_token(t_token *token);
void 	free_token(t_token **tokens);
void	handle_token_word(t_token *current, char **paths, bool *is_cmd_found);
void 	handle_token_redir(t_token *token);


t_token	*handle_word(char **input);
t_token *handle_double_quotes(char **input);
t_token	*handle_pipe(char **input);
t_token	*handle_redirection(char **input);
t_token *handle_single_quotes(char **input);

char	*extract_word(char *str, size_t len);

size_t	get_word_length(char *str);
size_t	get_double_quotes_length(char *str);
size_t	get_single_quotes_length(char *str);

bool	is_cmd(char **paths, char *cmd);
int		is_pipe(char c);
int		is_redirection(char c);
int		is_absolute_path(char *path);
int		is_dir(char *value);
int		is_file(char *value);

#endif
