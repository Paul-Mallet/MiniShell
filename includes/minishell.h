/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:47:37 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/13 19:19:31 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum    e_token_first
{
	WORD,
	SEPARATOR,
	PIPE,
	REDIR
}       t_token_first;

typedef enum	e_token_scnd
{
	CMD,
	ARG,
	FILES,
	DELIM,
	HEREDOC,
	APPEND,
	REDIR_INPUT,
	REDIR_OUTPUT
}		t_token_scnd;

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
}		t_redir;

void	init_mini_shell(t_env *env);

#endif