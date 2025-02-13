/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:40:44 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/13 15:41:06 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

void	print_alias_value(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
		{
			if (tmp->value)
				write(1, tmp->value, ft_strlen(tmp->value));
			return ;
		}
		tmp = tmp->next;
	}
}

char	*get_alias_name(char *str, int *i)
{
	char	*alias_name;
	int		start;
	int		len;

	start = *i + 1;
	len = 0;
	while (str[start + len] && (ft_isalnum(str[start + len]) ||
		str[start + len] == '_'))
		len++;
	alias_name = ft_substr(str, start, len);
	*i += len;
	return (alias_name);
}

void	ft_echo(char *str, t_env env, bool option_n)
{
	int		i;
	char	*alias_name;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			alias_name = get_alias_name(str, &i);
			if (alias_name)
			{
				print_alias_value(&env, alias_name);
				free(alias_name);
			}
		}
		else
			write(1, &str[i], 1);
		i++;
	}
	if (!option_n)
		write(1, "\n", 1);
}
