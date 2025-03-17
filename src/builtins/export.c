/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:39:54 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 19:17:33 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "parsing.h"

void	export_env_var(t_env **env, char *import)
{
	t_env	*current;
	t_env	*new;
	char	*key;

	current = *env;
	key = extract_key(import, 0);
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0) //!
		{
			free (current->value);
			current->value = ft_strdup(ft_strchr(import, '=') + 1);
			return ;
		}
		else
			current = current->next;
	}
	new = new_env_node(import);
	if (new)
		env_add_back(env, new);
	free(key);
}

void	ft_export(t_env *env, char **cmd)
{
	int	i;

	i = 0;
	if (!cmd[i + 1])
	{
		print_env(env);
		return ;
	}
	while (cmd[++i])
	{
		if (check_key_fmt(cmd[i]))
			export_env_var(&env, cmd[i]);
	}
}

bool	check_key_fmt(char *value)
{
	int		i;
	bool	has_equal;

	i = 0;
	has_equal = false;
	if (!value || (!ft_isalpha(value[i]) && value[i] != '_'))
	{
		printf("export: `%s': not a valid identifier\n", value);
		return (false);
	}
	while (value[i])
	{
		if (value[i] == '=')
		{
			has_equal = true;
			break;
		}
		else if (!ft_isalnum(value[i]) && value[i] != '_')
		{
			printf("export: `%s': not a valid identifier\n", value);
			return (false);
		}
		i++;
	}
	return (has_equal);
}

bool	check_if_value(char *value)
{
	int	i;

	i = 0;
	while(value[i])
	{
		if (value[i] == '=' && value[i + 1])
			return (true);
		i++;
	}
	return (false);
}
