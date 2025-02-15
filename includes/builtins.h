/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:43:19 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/12 18:00:08 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "./minishell.h"

/*
	builtins handler
*/
void	ft_builtins(char *input, t_env *env);

/*
	echo
*/
// void 	ft_echo(void);

/*
	cd
*/
// void 	ft_cd(void);

/*
	pwd
*/
void	ft_pwd(void);

/*
	export
*/
void	ft_export(char *import, t_env **env);
void	add_env(char *import, t_env **env);
void	update_env(t_env *env, char *value);
void	free_key_and_value(char *key, char *value);

/*
	unset
*/
void 	ft_unset(t_env **env, char *key);

/*
	env
*/
t_env	*new_env_node(char *entry);
t_env	*import_env(char **env);
void 	ft_env(t_env *env);
void 	free_env(t_env *env);
/*
	exit
*/
void	ft_exit(t_env *env);

#endif