/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:47:37 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/06 17:34:19 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
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
	ERR_UNKNOWN
}				t_error_code;

typedef enum	e_token_first
{
	WORD,
	SEPARATOR,
	PIPE,
	REDIR
}		t_token_first;

typedef enum	e_token_scnd
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
	IS_BUILTIN,			//to be skipped by build_cmd() 10
	IS_SEPARATOR,
	UNKNOW_SUBTYPE,
}		t_token_scnd;

typedef struct	s_token
{
	t_token_first	type;
	t_token_scnd	subtype;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}		t_token;

typedef struct	s_env
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
	int				fd[2];   // Pipe entre commandes 
	char			**cmd;  //OK build_cmd
	struct s_redir	*redir;  // Gestion de "<", "<<", ">" et ">>"
}		t_cmd;

/*
	Struct de redirection
	type, <<, >>, <, > (token)
	file, files concerned by redir
*/
typedef struct 	s_redir
{
	struct s_redir	*prev;
	struct s_redir	*next;
	char    *file;      // Nom du fichier (NULL si pas de redirection)
	int     fd;         // Descripteur du fichier (-1 si pas ouvert)
	char	*value;
	bool	in_redir;
	bool	out_redir;
	bool    append;
	bool    heredoc;
	char    *delimiter; // Delimiteur pour heredoc (NULL si pas de heredoc)
}		t_redir;

typedef struct	s_data
{
	t_cmd			*cmds;
	t_env			*env;
	t_token			*tokens;
	t_error_code	code;
	int				exit_code;
}		t_data;

void	init_data(t_data *data);
void	init_mini_shell(t_data *data, char **envp);
int		error_handling(t_error_code code, char *cmd);

#endif
