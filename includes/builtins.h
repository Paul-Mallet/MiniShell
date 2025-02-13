/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:43:19 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/13 15:25:29 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "./minishell.h"

/*
	builtins handler
*/
void	ft_builtins(char *input, t_env *env, t_alias *alias);

/*
	echo
*/
void	print_alias_value(t_alias *alias_lst, char *name);
char	*get_alias_name(char *str, int *i);
void	ft_echo(char *str, t_alias *alias, bool option_n);

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
void	ft_exit(t_env *env, t_alias *alias);

/*
	alias
*/
void	free_alias(t_alias *alias);
void	add_alias(t_alias **list, t_alias *new);
t_alias	*create_alias(char *name, char *value);

#endif