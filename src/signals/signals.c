/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:15:06 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/24 11:44:17 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

volatile sig_atomic_t	g_exit_code = 0;

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
		void     (*sa_handler)(int);
		//SIG_DFL, SIG_IGN, *void function_name(int signal);
		void     (*sa_sigaction)(int, siginfo_t *, void *);
		sigset_t   sa_mask; //block signals during exec of routine
		int        sa_flags;
		void     (*sa_restorer)(void);
	};
	
	Ctrl + D = EOF in heredoc

	g_pid = 130 = 128 + 2(SIGINT);
	g_pid = 131 = 128 + 3(SIGQUIT);
	-> used for exit_status

	sa.sa_flags = SA_RESTART;
		-> reload syst calls interupt by signal (read(), write())
*/

// void	sigint_heredoc_handler(void)
// {
// 	printf("^C\n");
// 	signal(SIGQUIT, SIG_DFT);
// }

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 130;
}

void	signals_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
