/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:21:03 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/14 15:36:28 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H
# include "./minishell.h"

# include "../includes/minishell.h"
# include "../includes/builtins.h"
# include "../includes/parsing.h"

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

int		count_cmds(t_cmd *cmds);
void	check_heredoc(t_data *data);
void	*heredoc_name(t_redir *redir);

/*
	redir managing
*/
int		redir_managing(t_cmd *cmds);
bool	check_if_is_last_in(t_redir *redir);
bool	check_if_is_last_out(t_redir *redir);
bool	check_redir(t_cmd *cmds);
bool	redir_input(t_redir *redir, bool last_cmd);
bool	redir_output(t_redir *redir, bool last_cmd);
bool	redir_append(t_redir *redir, bool last_cmd);
bool	redir_heredoc(t_redir *redir, bool last_cmd);


bool	write_heredoc(t_redir *redir);
void	fork_heredoc(t_data *data);
void	heredoc_managing(t_data *data);

/*
	exec
*/
int		exec(t_data *data);
char	**make_env(t_env *env);
int		count_cmds(t_cmd *cmds);
void	wait_all(t_data *data);
void	free_paths(char **paths, char *path);
bool	is_builtins(char *cmd);

int		exec_simple_cmd(t_data *data);
int		exec_multiple_cmds(t_data *data);
int		exec_command(t_cmd *cmds, t_data *data, int *i);
int		exec_last_cmd(t_cmd *cmds, t_data *data, int *i);
int		exec_first_cmd(t_cmd *cmds, t_data *data, int *i);

void	executing_command(t_cmd *cmds, char *path, t_data *data);
void	executing_first_cmd(t_cmd *cmds, char *path, t_data *data);
void	executing_last_cmd(t_cmd *cmds, char *path, t_data *data);
void	executing_simple_cmd(t_data *data, char *path);

void	free_exec(t_data *data);
int		error_path(char **paths, char *prompt, t_data *data);
void	close_all_pipes(t_cmd *cmd);
void	free_data_children(t_data *data);

#endif
