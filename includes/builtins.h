/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:43:19 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/12 14:00:01 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "./minishell.h"

/*
	env
*/
t_env   *new_env_node(char *entry);
t_env   *import_env(char **env);
void    print_env(t_env *env);
void    free_env(t_env *env);

/*
	unset
*/
void unset_env(t_env **env, char *key);

#endif