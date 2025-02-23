/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:43:19 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/23 12:26:11 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H
# include "./minishell.h"

/*
	builtins conditions
*/
void	ft_builtins(t_data *data);

/*
	echo
*/
int	ft_echo(t_token *tokens);
int	ft_echo_next(t_token *tokens, bool arg_n);

/*
	cd
*/
void	ft_cd(char *path);

/*
	pwd
*/
void	ft_pwd(void);

/*
	export
*/
void	ft_export(char *import, t_env **env);
void	print_export(t_env *env);
void	add_env(char *import, t_env **env);
void	update_env(t_env *env, char *value);
void	free_key_and_value(char *key, char *value);

/*
	unset
*/
void	ft_unset(t_env **env, char *key);

/*
	env
*/
t_env	*new_env_node(char *entry);
t_env	*import_env(char **env);
void	ft_env(t_env *env);
void	free_env(t_env **env);
void	env_add_back(t_env **env, t_env *new);

/*
	exit
*/
void	ft_exit(t_data *data, char *input, char *prompt);

#endif
