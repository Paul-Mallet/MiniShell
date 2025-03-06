// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamallet <pamallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:32:10 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/05 13:45:16 by pamallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/signals.h"
#include "signal.h"

volatile sig_atomic_t	g_pid = 0;

/*
	/bin/kill
	int kill(pid_t pid, int sig); return (0); on success
	gpid -> int kill(-pid, int sig);
	all process in group -> int kill(0, int sig);
	all process instead kill & init -> int kill(-1, int sig);
	kill() = /bin/kill -L -l

	can't modif SIGKILL & SIGSTOP actions
	int sigaction(int signum, const struct sigaction *restrict act,
    		struct sigaction *restrict oldact); return (0); on success (-1 + errno)
	

	i++;
	num = ft_itoa(i);
	hd_file = join_lines("/tmp/heredoc_", num);
	redir->fd = open(hd_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
	{
		i++;
		free(hd_file);
		free(num);
		heredoc_name(redir);
	}
	free(hd_file);
	free(num);
	return (hd_file);
}
	man sigaction
	struct sigaction {
		void     (*sa_handler)(int); //SIG_DFL, SIG_IGN, *void function_name(int signal);
		void     (*sa_sigaction)(int, siginfo_t *, void *);
		sigset_t   sa_mask; //block signals during exec of routine
		int        sa_flags;
		void     (*sa_restorer)(void);
	};
*/
static void	sigint_handler(int sig)
{
	(void)sig;
	if (g_pid == 0)
	{
		printf("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		write(1, "OK\n", 3);
}

void	signals_handler(void)
{
	struct sigaction	sa;

	// ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	// sa.sa_flags = SA_RESTART; //avoid readline() bug
	sa.sa_flags = 0; //avoid readline() bug
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

//Ctrl + D = EOF in heredoc, 