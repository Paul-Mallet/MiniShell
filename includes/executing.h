/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:21:03 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/23 18:26:19 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H
# include "./minishell.h"

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"

char	*construct_path(char *dir, char *cmd);
char	*find_path(char **paths, char *cmd);
char	**get_path_vrbl(t_env *env);
void	free_strs(char **paths);

char	**malloc_cmd(t_token *tokens);
char	**build_cmd(t_token	*tokens, char **cmd);
void	 print_cmd(char **cmd);
void	init_commands_t_cmd(t_token *tokens);

#endif
