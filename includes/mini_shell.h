/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:47:37 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/11 18:38:27 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/stat.h>

//FILE, <, >, <<, >>, PIPE ematon

/*
    Struct de tokens
*/
typedef enum    e_token_first
{
    WORD
    SEPARATOR
    PIPE
    REDIR
}       t_token_first;

/*
    Enum de sub_tokens
*/
typedef enum    e_token_scnd
{
    CMD
    ARG
    DELIM
    HEREDOC
    APPEND
    REDIR_INPUT
    REDIR_OUTPUT
}       t_token_scnd;

/*
    Struct de env
*/
typedef struct  s_env
{
    char    *key;
    char    *value;
    s_env   *next;
}       t_env;

/*
    Struct de cmds
*/
typedef struct s_cmd
{
    s_cmd   *prev;
    s_cmd   *next;
    int     fd[2];
    int     fd_input;
    int     fd_output;
    char    *cmd;
    char    *arg;
    bool    is_hd;
}       t_cmd;

/*
    Struct de redirection
    type, <<, >>, <, > (token)
    file, files concerned by redir
*/
typedef struct s_redir
{
    t_token_scnd    type;
    char    *file;
}       t_redir;

#endif