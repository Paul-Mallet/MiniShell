/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:21:03 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/01 18:42:56 by abarahho         ###   ########.fr       */
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
void	print_redir(t_redir *redir);
void	free_redir(t_redir **redirs);
// t_redir	*new_redir(t_token *tokens);
// void	redir_add_back(t_redir **lst, t_redir *new);
// void	free_redir(t_redir **redirs);

bool	check_tokens(t_token *tokens);

int		count_cmds(t_cmd *cmds);
void	exec(t_data *data);
void	check_heredoc(t_data *data);
char	*heredoc_name(void);

/*
	redir managing
*/
void	redir_managing(t_data *data);
int		check_redir(t_cmd *cmd);
bool	redir_input(t_redir *redir, bool last_cmd);
bool	redir_output(t_redir *redir, bool last_cmd);
bool	redir_append(t_redir *redir, bool last_cmd);
bool	redir_heredoc(t_redir *redir);

/*
	exec
*/

void	exec(t_data *data);
int		exec_command(t_data *data, char **envp, int *prev_pipe, bool is_last_cmd);
char	**make_env(t_env *env);
void	setup_pipes(t_cmd *cmd, int *prev_pipe, bool is_last_cmd);
int		count_cmds(t_cmd *cmds);
void	check_heredoc(t_data *data);





#endif
