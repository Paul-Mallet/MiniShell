/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:09:37 by paul_mallet       #+#    #+#             */
/*   Updated: 2025/02/18 19:49:04 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

#define UNKNOWN_SUBTYPE -1


static bool is_absolute_path(char *path)
{
    if (!path)
        return (false);
    return (path[0] == '/');
}

void handle_token_redir(t_token *token)
{
	if (!ft_strcmp(token->value, ">>"))
		token->subtype = APPEND;
	else if (!ft_strcmp(token->value, "<<"))
		token->subtype = HEREDOC;
	else if (token->value[0] == '<')
		token->subtype = REDIR_INPUT;
	else if (token->value[0] == '>')
		token->subtype = REDIR_OUTPUT;
}

void handle_token_word(t_token *token, char **paths, bool is_cmd_found)
{
    if (token->prev && token->prev->subtype == HEREDOC)
    {
        token->subtype = DELIM; // Cas du délimiteur pour HEREDOC
    }
    else if (token->prev && token->prev->type == REDIR)
    {
        // Si le token précédent est une redirection, vérifiez si ce token est un fichier valide
        if (is_file(token->value))
            token->subtype = FILES; // Cas des fichiers pour les redirections
        else
            token->subtype = UNKNOWN_SUBTYPE; // Si le fichier n'existe pas, marquez-le comme inconnu
    }
    else if (!(is_cmd_found) && (is_cmd(paths, token->value) || is_absolute_path(token->value)))
    {
        token->subtype = CMD; // Cas d'une commande
        is_cmd_found = true;
    }
    else if (is_cmd_found)
    {
        token->subtype = ARG; // Cas d'un argument de commande
    }
    else
    {
        token->subtype = UNKNOWN_SUBTYPE; // Cas par défaut
    }
}
// {
// 	if (token->prev && token->prev->subtype == HEREDOC)
// 		token->subtype = DELIM;
// 	else if (token->prev && token->prev->type == REDIR)
// 	{
// 		token->subtype = CMD;
// 		is_cmd_found = true;
// 	}
// 	else if (is_file(token->value))
// 		token->subtype = FILES;
// 	else if (is_cmd_found)
// 		token->subtype = ARG;
// 	else
// 		token->subtype = UNKNOWN_SUBTYPE;
// }

void handle_pipe_sep(t_token *token, bool is_cmd_found)
{
	token->subtype = UNKNOWN_SUBTYPE;
	is_cmd_found = false;
}

void second_tokenization(t_token *tokens, t_env *env)
{
	char	**paths;
	t_token	*current;
	bool	is_cmd_found;

	current = tokens;
	paths = get_path_vrbl(env);
	is_cmd_found = false;
	// if (!paths) error_handling();
	while (current)
	{
		if (current->type == REDIR && current->value)
			handle_token_redir(current);
		else if (current->type == WORD && current->value)
			handle_token_word(current, paths, is_cmd_found);
		else if (current->type == PIPE || current->type == SEPARATOR)
			handle_pipe_sep(current, is_cmd_found);
		else
			current->subtype = UNKNOWN_SUBTYPE;
		current = current->next;
	}
	free_paths(paths);
}
