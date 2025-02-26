/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:21:03 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/26 19:01:48 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H
# include "./minishell.h"

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"

/*
	get paths for
*/
char	*construct_path(char *dir, char *cmd);
char	*find_path(char **paths, char *cmd);
char	**get_path_vrbl(t_env *env);
void	free_strs(char **paths);

t_token	*to_pipe_or_last_token(t_token *tokens);

/*
	t_cmd, linked list
	* char		**valid_cmd
*/
t_cmd	*init_cmd_struct(t_token *tokens);
void	cmd_struct_add_back(t_cmd **cmds, t_cmd *new);
t_cmd	*new_cmd(char **cmds);
char	**malloc_cmd(t_token *tokens);
char	**build_cmd(t_token	*tokens, char **cmd);
void	print_cmds(char **cmds);
void 	print_cmd_struct(t_cmd *cmd);
void 	free_cmd_struct(t_cmd **cmds);

/*
	t_redir
*/
void	init_redirs(t_token *tokens, t_cmd *new);
void	fill_redir(t_token *tokens, t_redir *new);
void 	print_redir(t_redir *redir);
void	print_redirtamere(t_redir *redir);

// t_redir	*new_redir(t_token *tokens);
// void	redir_add_back(t_redir **lst, t_redir *new);
// void	free_redir(t_redir **redirs);

bool	check_tokens(t_token *tokens);

int	count_cmds(t_cmd *cmds);

#endif
