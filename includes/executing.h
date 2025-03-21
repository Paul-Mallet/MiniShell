/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:21:03 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/21 17:16:59 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H
# include "./minishell.h"

# include "minishell.h"
# include "builtins.h"
# include "parsing.h"

/*
	get paths for
*/
char	*construct_path(char *dir, char *cmd);
char	*check_path(t_data *data, char *cmd);
char	*find_path(t_data *data, char **path_var, char *cmd);
char	**get_path_var(t_env *env);
void	free_strs(char **paths);

t_token	*to_pipe_or_last_token(t_token *tokens);

/*
	t_cmd, linked list
	* char		**valid_cmd
*/
bool	init_cmd_struct(t_data *data);
void	cmd_struct_add_back(t_cmd **cmds, t_cmd *new);
t_cmd	*new_cmd(char **cmds);
char	**malloc_cmd(t_token *tokens);
void	init_id_cmds(t_cmd *cmds);
void	print_cmds(char **cmds);
void	print_cmd_struct(t_cmd *cmd);
void	free_cmd_struct(t_cmd **cmds);

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
void	heredoc_filename(t_redir *redir);
void	fork_heredoc(t_redir *redir, t_data *data);

/*
	redir managing
*/
bool	check_if_is_last_in(t_redir *redir, t_cmd *cmd);
bool	check_if_is_last_out(t_redir *redir, t_cmd *cmd);
void	check_redir(t_cmd *cmds, t_data *data);
void	redir_input(t_redir *redir, bool last_cmd, t_data *data);
void	redir_output(t_redir *redir, bool last_cmd, t_data *data);
void	redir_append(t_redir *redir, bool last_cmd, t_data *data);
void	redir_heredoc(t_redir *redir, bool last_cmd);

bool	write_heredoc(t_redir *redir);
void	heredoc_managing(t_data *data);

/*
	exec
*/
void	exec(t_data *data);
void	exec_multiple_cmds(t_data *data, int nb_cmd);
char	**make_env(t_env *env);
int		count_cmds(t_cmd *cmds);
void	wait_all(t_data *data);
bool	is_builtins(char *cmd);

void	exec_command(t_cmd *cmds, t_data *data, t_cmd_order nbr, int *i);
void	exec_simple_cmd(t_data *data);
void	executing_command(t_cmd *cmds, char *path, t_data *data,
			t_cmd_order nbr);
void	executing_simple_cmd(t_data *data);

void	free_exec(t_data *data);
int		error_path(char **paths, char *prompt, t_data *data);
void	close_all_pipes(t_cmd *cmd);
void	close_pipes(t_cmd *cmd);
void	free_data_children(t_data *data);

#endif
