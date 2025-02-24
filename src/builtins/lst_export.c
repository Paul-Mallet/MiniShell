// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   lst_export.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/24 14:19:36 by abarahho          #+#    #+#             */
// /*   Updated: 2025/02/24 17:12:20 by abarahho         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"
// #include "../../includes/builtins.h"

// t_export	*new_exp_node(char *entry)
// {
// 	t_export   *new;
// 	char    	*sep;

// 	if (!entry)
// 		return (NULL);
// 	sep = ft_strchr(entry, '=');
// 	if (!sep)
// 		return (NULL);
// 	new = (t_export*)malloc(sizeof(t_export));
// 	if (!new)
// 		return (NULL);
// 	new->key = ft_strndup(entry, sep - entry);
// 	new->value = ft_strdup(sep + 1);
// 	new->next = NULL;
// 	if (!new->key || !new->value)
// 	{
// 		free(new->key);
// 		free(new->value);
// 		free(new);
// 		return (NULL);
// 	}
// 	return (new);
// }

// void	exp_add_back(t_env **env, t_export *new)
// {
// 	t_env	*curr;

// 	if (!exp || !new)
// 		return ;
// 	if (!*exp)
// 	{
// 		*exp = new;
// 		return ;
// 	}
// 	curr = *exp;
// 	while (curr->next != NULL)
// 		curr = curr->next;
// 	curr->next = new;
// }

// void	free_exp(t_export **export)
// {
// 	t_export	*tmp;
// 	t_export	*next;

// 	if (export == NULL)
// 		return ;
// 	tmp = *export;
// 	while (tmp != NULL)
// 	{
// 		next = tmp->next;
// 		free(tmp->key);
// 		free(tmp->value);
// 		free(tmp);
// 		tmp = next;
// 	}
// 	*export = (NULL);
// }

// void print_env(t_env *env, t_export *export)
// {
// 	while (env)
// 	{
// 		ft_printf("declare -x %s=%s\n", env->key, env->value);
// 		env = env->next;
// 	}
// }
