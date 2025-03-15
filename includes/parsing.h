/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:43:05 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/15 18:08:48 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "./minishell.h"
# include "./executing.h"

typedef struct	s_valid_quotes
{
	int	sgle_cnt;
	int dble_cnt;
	int	is_in_sgle;
	int	is_in_dble;
}		t_valid_quotes;

typedef struct s_expand
{
	char	*res;
	char	*tmp;
	int		i;
	int		j;
	int		k;
}		t_expand;

/*
	expander
*/
int		expand_length(char *value, t_data *data);
char	*expander(char *value, t_data *data);
char	*expanding(char *value, t_data *data, int len, t_expand);
int		get_value_len(char *value, int i, t_data *data);
char	*get_key_value(char *value, int i, t_data *data);
char	*extract_key(char *value, int i);
int		check_key(char c);


/*
	lexer checks if input is valid
	also frees input if invalid
*/
bool	ft_lexer(t_data *data);

/*
	parsing correctly formats input before tokenize it
	* trim 1rst & last spaces
	* reduce spaces between each word to 1
*/
void	ft_parsing(char *value, t_data *data);
void	get_expanded(t_token *tokens, t_data *data);
int		check_cmd_tokens(t_token *tokens);
void	join_tokens(t_token **tokens);
void	remove_token(t_token *token);
void	remove_empty_token(t_token *tokens);
bool	if_double_quotes(char *value);
bool	if_single_quotes(char *value);

/*
	1rst tokenizer separates words of input by types
*/
t_token	*new_token(t_token_first type, t_token_scnd subtype, char *value);
void	token_add_back(t_token **lst, t_token *new);
t_token	*first_tokenization(char *input);
void	second_tokenization(t_data *data);
void	print_token(t_token *token);
void 	free_tokens(t_token **tokens);
void	handle_token_word(t_token *current);
void 	handle_token_redir(t_token *token);
char	*check_expanding(char *input, t_data *data);

t_token	*handle_word(char **input);
t_token *handle_double_quotes(char **input);
t_token	*handle_pipe(char **input);
t_token	*handle_redirection(char **input);
t_token *handle_single_quotes(char **input);
t_token	*handle_exit_code(char **input, t_data *data);

char	*extract_word(char *str, size_t len);

size_t	get_word_length(char *str);
void	remove_single_quotes(t_token *tokens);
void	remove_double_quotes(t_token *tokens);
void	fill_without_quotes(char *dest, char *src, char c);
int		len_without_qtes(char *value, char c);
int		count_ins_quotes(char *value, int *i, char c);
size_t	get_double_quotes_length(char *str);
size_t	get_single_quotes_length(char *str);
void	remove_join_quotes(t_token *tokens, char c);

bool		is_cmd(char **paths, char *cmd, t_data *data);
bool		is_executable(char *path, t_data *data);
bool		is_pipe(char c);
bool		is_redirection(char c);
bool		is_dir(char *value);

#endif
