/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:28:40 by abarahho          #+#    #+#             */
/*   Updated: 2025/02/14 11:35:04 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

t_token	*ft_lexer(char *input)
{
    t_token	*tokens;
    int		i;

    i = 0;
    tokens = NULL;
    while (input[i])
    {
		if (input[i] == '|')
			tokens = is_a_pipe(input, &i);
		if (input[i] == '<' || input[i] == '>')
			tokens = is_a_redir(input, &i);
		if (!ft_isdigit(input[i]))
			tokens = is_a_word(input, &i);
    }
    return (tokens);
}

t_token	*ft_new_token(t_token_first type, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new), NULL);
	new->next = NULL;
	return (new);
}

void	ft_token_add_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	ft_free_token(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}
void free_token(t_token **token)
{
	t_env	*tmp;
	t_env	*next;

	if (token == NULL)
		return ;
	tmp = *token;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*token = (NULL);
}