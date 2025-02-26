/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:59:59 by pamallet          #+#    #+#             */
/*   Updated: 2025/02/26 17:48:20 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"
#include "../includes/executing.h"

void	init_data(t_data *data)
{
	data->cmds = NULL;
	data->env = NULL;
	data->export = NULL;
	data->tokens = NULL;
	data->exit_code = 0;
}

static char	*get_prompt(void)
{
	char	*prompt;
	char	name[BUFFER_SIZE];

	if (!getcwd(name, BUFFER_SIZE))
	{
		perror("getcwd error");
		return (NULL);
	}
	prompt = ft_strjoin(name, "$ ");
	return (prompt);
}
void print_commads(t_cmd *cmds)
{
    t_cmd *current = cmds;
    t_redir *current_redir;
    int i;

    printf("=== Command List ===\n");
    while (current)
    {
        printf("\nCommand:\n");
        printf("  Args: ");
        if (current->cmd)
        {
			i = 0;
            while (current->cmd[i])
                printf("\"%s\" ", current->cmd[i++]);
        }
        else
            printf("(empty)");

        printf("\n");
        current_redir = current->redir;
        while (current_redir)
        {
            printf("  Redirection: Type \"%s\"", current_redir->value);
            if (current_redir->file)
                printf(", File \"%s\"", current_redir->file);
            if (current_redir->append)
                printf(" (Append)");
            if (current_redir->heredoc)
                printf(" (Heredoc, Delimiter \"%s\")", current_redir->delimiter);
            printf("\n");
            current_redir = current_redir->next;
        }
        printf("----------------------\n");
        current = current->next;
    }
}

void	init_mini_shell(t_data *data, char **envp)
{
	char 	*input;
	char	*prompt;

	data->env = import_env(envp);
	prompt = get_prompt();
	if (!prompt)
		return;
	while ((input = readline(prompt)))
	{
		if (input)
			add_history(input);
		ft_lexer(input);
		data->tokens = ft_parsing(input, data->env);
		// data->cmds = init_cmd_struct(data->tokens);
		ft_builtins(data);
		free(prompt);
		prompt = get_prompt();
		if (!prompt)
			break ;
		// check_tokens(data->tokens);
		// ft_exec(data);
		print_token(data->tokens);
		free_tokens(&data->tokens);
		free(input);
	}
}
