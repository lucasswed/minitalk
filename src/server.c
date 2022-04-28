/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:27:08 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/04/28 13:36:07 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static char	c = 0xFF;
	static int	bits = 0;

	(void)context;
	if (signum == SIGUSR1)
		c |= 0x80 >> bits;
	else if (signum == SIGUSR2)
		c ^= 0x80 >> bits;
	if (++bits == 8)
	{
		ft_putchar_fd(c, 1);
		if (!c)
		{
			if (kill(info->si_pid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		bits = 0;
		c = 0xFF;
	}
}

int	main(void)
{
	struct sigaction	sig;
	sigset_t			block;
	pid_t				pid;

	sigemptyset(&block);
	sigaddset(&block, SIGUSR1);
	sigaddset(&block, SIGUSR2);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = sig_handler;
	pid = getpid();
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
}
