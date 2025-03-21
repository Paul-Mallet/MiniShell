/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:43:05 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/21 17:23:32 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "./minishell.h"
# include "./executing.h"

typedef struct s_valid_quotes
{
	int	sgle_cnt;
	int	dble_cnt;
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

bool	ft_lexer(t_data *data);

bool	ft_parsing(char *value, t_data *data);
int		ft_isspaces(char *input);
void	get_expanded(t_token *tokens, t_data *data);
void	join_tokens(t_token **tokens);
void	remove_token(t_token *token);

t_token	*new_token(t_token_first type, t_token_scnd subtype, char *value);
void	token_add_back(t_token **lst, t_token *new);
t_token	*first_tokenization(char *input);
void	subtyping_tokens(t_data *data);
void	print_token(t_token *token);
void	free_tokens(t_token **tokens);
void	handle_token_word(t_token *current);
void	handle_token_redir(t_token *token);

t_token	*handle_word(char **input);
t_token	*handle_double_quotes(char **input);
t_token	*handle_pipe(char **input);
t_token	*handle_redirection(char **input);
t_token	*handle_single_quotes(char **input);

char	*extract_word(char *str, size_t len);

size_t	get_word_length(char *str);
size_t	get_double_quotes_length(char *str);
size_t	get_single_quotes_length(char *str);

int		is_executable(t_data *data, char *cmd);
int		is_dir(char *value);

#endif
