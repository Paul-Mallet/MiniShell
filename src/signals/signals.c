/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarahho <abarahho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:32:10 by abarahho          #+#    #+#             */
/*   Updated: 2025/03/04 17:15:34 by abarahho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/signals.h"

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
static void	sigint_handler(int signal)
{
	//pid_t	pid

	if (g_pid != 0 && signal == SIGINT) //child process
	{
		printf("\nIntercepted SIGINT on child!\n\n");
		// if (kill(pid, signal) == -1)
		// {
			// perror("signals");
			// exit(EXIT_FAILURE);
		// }
	}
}

static void	sigquit_handler(int signal)
{
	//pid_t	pid

	if (signal == SIGQUIT)
		printf("\nIntercepted SIGQUIT!\n\n");
	/*
	if (kill(pid, signal) == -1)
	{
		perror("signals");
		exit(EXIT_FAILURE);
	}
	*/
}

static void	set_signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_RESTART; //avoid readline() bug
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);

	act.sa_handler = &sigquit_handler;
	sigaction(SIGQUIT, &act, NULL);
}

void	signals_handler(void)
{
	set_signal_action();
}