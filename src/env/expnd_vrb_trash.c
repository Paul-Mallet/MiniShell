/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnd_vrb_trash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:17:53 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/13 17:17:55 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
