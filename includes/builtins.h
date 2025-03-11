/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:43:19 by pamallet          #+#    #+#             */
/*   Updated: 2025/03/11 16:22:17 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H
# include "./minishell.h"

# define PATH_BUFFER 1024

/*
	builtins conditions
*/
int		ft_builtins(t_data *data, t_cmd *cmd);

/*
	echo
*/
int		ft_echo(char **cmds);
int		ft_echo_next(char **cmd, int i, bool arg_n);

/*
	cd
*/
void	ft_cd(t_env *env, char *path);

/*
	pwd
*/
void	ft_pwd(void);

/*
	unset
*/
void	ft_unset(t_env **env, char **cmd);
void	unset_env_var(t_env **env, char *key);

/*
	env
*/
void 	ft_env(t_env *env);
t_env	*new_env_node(char *entry);
t_env	*import_env(char **env);
void	env_add_back(t_env **env, t_env *new);
void	free_env(t_env **env);
void	print_env(t_env *env);
void	set_env_values(t_env *new, char *entry, char *sep);

/*
	export
*/

bool	check_key_fmt(char *value);
bool	check_if_value(char *value);
void	ft_export(t_env *env, char **cmd);


/*
	exit
*/
void	ft_exit(t_data *data);

#endif
