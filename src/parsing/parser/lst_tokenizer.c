/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:38:28 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/22 14:28:52 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_token	*new_token(t_token_first type, t_token_scnd subtype, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	free(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->subtype = subtype;
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	token_add_back(t_token **lst, t_token *new)
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
	new->prev = current;
}

void	free_tokens(t_token **tokens)
{
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		next = (*tokens)->next;
		free((*tokens)->value);
		free(*tokens);
		(*tokens) = next;
	}
	*tokens = NULL;
}

// void	print_token(t_token *token)
// {
// 	t_token	*current;
// 	int		i;

// 	i = 0;
// 	current = token;
// 	printf("\n");
// 	while (current)
// 	{
// 		ft_dprintf(2, "Token n*: %d\n", i++);
// 		ft_dprintf(2, "Type: %s\n",
// 			get_token_type_string(current->type));
// 		ft_dprintf(2, "Subtype: %s\n",
// 			get_token_subtype_string(current->subtype));
// 		ft_dprintf(2, "Value: %s\n\n", current->value);
// 		current = current->next;
// 	}
// }