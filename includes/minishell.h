/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul_mallet <paul_mallet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:47:37 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/16 13:21:27 by paul_mallet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>

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
	DELIM,
	APPEND,
	HEREDOC,
	REDIR_INPUT,
	REDIR_OUTPUT
}		t_token_scnd;

typedef struct	s_token
{
	t_token_first	type;
	t_token_scnd	subtype;
	char			*value;
	struct s_token	*prev; //to determine current subtype
	struct s_token	*next;
}		t_token;

typedef struct	s_env
{
	char			*key;
	char			*value;
	bool			is_env;
	struct s_env	*next;
}		t_env;

typedef struct s_cmd
{
	struct s_cmd	*prev;
	struct s_cmd	*next;
	int				fd[2];
	int				fd_input;
	int				fd_output;
	char			*cmd;
	char			*arg;
	bool			is_hdoc;
}		t_cmd;

/*
	Struct de redirection
	type, <<, >>, <, > (token)
	file, files concerned by redir
*/
typedef struct	s_redir
{
	t_token_scnd	type;
	char			*file;
	int				id;
}		t_redir;

typedef struct	s_data
{
	struct t_cmd	*cmds;
	struct t_env	*env;
	struct t_redir	*redir;
	struct t_token	*tokens;
	int				exit_code;
}		t_data;

void	init_mini_shell(t_env *env);

#endif
