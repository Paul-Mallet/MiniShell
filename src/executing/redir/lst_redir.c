/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:15:15 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/17 18:37:09 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"

t_redir	*new_redir(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = NULL;
	redir->fd = -1;
	redir->value = NULL;
	redir->in_redir = false;
	redir->out_redir = false;
	redir->append = false;
	redir->heredoc = false;
	redir->delimiter = NULL;
	redir->prev = NULL;
	redir->next = NULL;
	return (redir);
}

void	fill_redir(t_token *tokens, t_redir *new)
{
	if (tokens->next && tokens->next->subtype == FILES)
		new->file = ft_strdup(tokens->next->value);
	else if (tokens->next->next && tokens->next->next->subtype == FILES)
		new->file = ft_strdup(tokens->next->next->value);
	new->value = ft_strdup(tokens->value);
	if (tokens->subtype == APPEND)
		new->append = true;
	else if (tokens->subtype == REDIR_INPUT)
		new->in_redir = true;
	else if (tokens->subtype == REDIR_OUTPUT)
		new->out_redir = true;
	else if (tokens->subtype == HEREDOC)
	{
		new->heredoc = true;
		if (tokens->next && tokens->next->subtype == DELIM)
			new->delimiter = ft_strdup(tokens->next->value);
		else if (tokens->next->next && tokens->next->next->subtype == DELIM)
			new->delimiter = ft_strdup(tokens->next->next->value);
	}
	// print_redir(new);
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*current;

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

void	init_redirs(t_token *tokens, t_cmd *new_cmd)
{
	t_redir	*head;
	t_redir	*new;
	t_token	*current;

	head = NULL;
	current = tokens;
	while(current && current->subtype != IS_PIPE) //stop PIPE
	{
        if (current->type == REDIR)
		{
		    new = new_redir();
			if (!new)
				return ;
			fill_redir(current, new);
			redir_add_back(&head, new);
		}
		current = current->next;
	}
	new_cmd->redir = head;
}

void	free_redir(t_redir **redirs)
{
	t_redir	*current;
	t_redir	*next;

	if (!redirs || !*redirs)
		return;
	current = *redirs;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		if (current->value)
			free(current->value);
		if (current->delimiter)
			free(current->delimiter);
		free(current);
		current = next;
	}
	*redirs = NULL;
}
