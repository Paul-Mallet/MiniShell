/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:43:19 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/12 17:40:25 by pamallet         ###   ########.fr       */
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
	pwd
*/
void	ft_pwd(void);

/*
	unset
*/
void 	ft_unset(t_env **env, char *key);

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