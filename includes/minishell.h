/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:47:37 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/22 16:07:22 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_cmd_order
{
	SIMPLE_CMD,
	FIRST_CMD,
	MID_CMD,
	LAST_CMD
}			t_cmd_order;

typedef enum e_error_code
{
	ERR_FILE_NOT_FOUND,
	ERR_ARGS,
	ERR_PERMISSION_DENIED,
	ERR_CMD_NOT_FOUND,
	ERR_DOUBLE_PIPES,
	ERR_PIPE_FAILURE,
	ERR_FORK_FAILURE,
	ERR_UNCLOSED_QUOTES,
	ERR_UNKNOWN,
	SYNTAX_ERROR_NEAR_TOKEN
}				t_error_code;

typedef enum e_token_first
{
	WORD,
	SEPARATOR,
	PIPE,
	REDIR
}		t_token_first;

typedef enum e_token_scnd
{
	CMD,
	ARG,
	FILES,
	DIR,
	DELIM,
	APPEND,
	HEREDOC,
	REDIR_INPUT,
	REDIR_OUTPUT,
	IS_PIPE,
	IS_SEPARATOR,
	UNKNOW_SUBTYPE,
}		t_token_scnd;

typedef struct s_token
{
	t_token_first	type;
	t_token_scnd	subtype;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}		t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

/* 
	Cmd between pipes, which handle redirs
*/
typedef struct s_cmd
{
	struct s_cmd	*prev;
	struct s_cmd	*next;
	int				fd[2];
	char			**cmd;
	struct s_redir	*redir;
	int				id;
	bool			has_input;
	bool			has_output;
}		t_cmd;

/*
	Struct de redirection
	type, <<, >>, <, > (token)
	file, files concerned by redir
*/
typedef struct s_redir
{
	struct s_redir	*prev;
	struct s_redir	*next;
	char			*file;
	int				fd;
	char			*value;
	bool			in_redir;
	bool			out_redir;
	bool			append;
	bool			heredoc;
	char			*delimiter;
}		t_redir;

typedef struct s_data
{
	t_cmd			*cmds;
	t_env			*env;
	t_token			*tokens;
	t_error_code	code;
	int				*pids;
	char			*prompt;
	char			*input;
	char			**char_env;
	int				exit_code;
	int				stdin;
	int				stdout;
}		t_data;

void	init_data(t_data *data);
void	loop_minishell(t_data *data, char **envp);
void	free_data(t_data *data);
void	free_processing(t_data *data);
void	free_parsing(t_data *data);
void	free_simple_cmd(t_data *data);
void	free_strs(char **paths);
bool	check_tokens(t_data *data);
char	*expander(char *value, t_data *data);

/*
	expander
*/
char	*get_key_value(t_env *env, char *key);
char	*expand_variable(char *input, size_t *i, t_data *data);
void	add_expanding(char **expanded, char *value, size_t *i, t_data *data);
char	*expander(char *value, t_data *data);
void	add_index(char **expanded, char i);
char	*extract_key(char *value, int i);

#endif
