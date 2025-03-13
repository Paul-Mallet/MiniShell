/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:38:28 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/13 14:13:07 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

t_token	*new_token(t_token_first type, t_token_scnd subtype, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	free(value); // invalid free pas tout le temps allouer
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
	// t_token	*current;
	t_token	*next;

	if (!tokens || !*tokens)
		return;
	// current = *tokens;
	while (*tokens)
	{
		next = (*tokens)->next;
		free((*tokens)->value);
		free(*tokens);
		(*tokens) = next;
	}
	*tokens = NULL;
}

static const char	*get_token_type_string(int type)
{
	static const char *token_types[] = {
		"WORD", "SEPARATOR", "PIPE", "REDIR"
	};
	if (type >= 0 && type <= 3)
		return token_types[type];
	return "UNKNOWN_TYPE";
}

static const char *get_token_subtype_string(int subtype)
{
	static const char *token_subtypes[] = {
		"CMD", "ARG", "FILES", "DIR", "DELIM", 
		"APPEND", "HEREDOC", "REDIR_INPUT", "REDIR_OUTPUT",
		"IS_PIPE", "IS_SEPARATOR", "UNKNOW_SUBTYPE"
	};
	return token_subtypes[subtype];
}

void	print_token(t_token *token)
{
	t_token	*current;
	int		i;

	i = 0;
	current = token;
	printf("\n");
	while (current)
	{
		printf("Token n*: %d\n", i++);
		printf("Type: %s\n", get_token_type_string(current->type));
		printf("Subtype: %s\n", get_token_subtype_string(current->subtype));
		printf("Value: %s\n\n", current->value);
		current = current->next;
	}
}
