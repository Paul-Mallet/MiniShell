/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:43:19 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/25 09:02:12 by abarahho         ###   ########.fr       */
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
	unset
*/
void	ft_unset(t_env **env, t_token *tokens);
void	unset_env_var(t_env **env, char *key);

/*
	env
*/
void	ft_env(t_env *env);
t_env	*new_env_node(char *entry);
t_env	*import_env(char **env);
void	env_add_back(t_env **env, t_env *new);
void	free_env(t_env **env);
void	print_env(t_env *env);
void	set_env_values(t_env *new, char *entry, char *sep);

/*
	export
*/
t_export	*new_exp_node(char *entry);
t_export	*import_exp(char **env);
void		free_exp(t_export **export);
void		exp_add_back(t_export **exp, t_export *new);
bool		check_key_fmt(char *value);
bool		check_if_value(char *value);

void		ft_export(t_env *env, t_token *tokens);
void		update_exp(t_export *export, char *value);
void		free_key_and_value(char *key, char *value);

/*
	exit
*/
void	ft_exit(t_data *data, char *input, char *prompt);

#endif
