/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:43:19 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/12 16:43:35 by abarahho         ###   ########.fr       */
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
void    ft_env(t_env *env);
void    free_env(t_env *env);

/*
	unset
*/
void ft_unset(t_env **env, char *key);

/*
	exit
*/
void	ft_exit(t_env *env);

/*
	export
*/
void	ft_export(char *import, t_env **env);
void	add_env(char *import, t_env **env);
void	update_env(t_env *env, char *value);
void	free_key_and_value(char *key, char *value);

#endif