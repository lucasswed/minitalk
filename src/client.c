/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:38:14 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/04/28 13:37:03 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_msg(char *msg, int pid)
{
	int	i;
	int	bit;

	i = -1;
	while (msg[++i])
	{
		bit = -1;
		while (++bit < 8)
		{
			if (msg[i] & 0x80 >> bit)
			{
				if (kill(pid, SIGUSR1) == -1)
					exit(EXIT_FAILURE);
			}
			else
				if (kill(pid, SIGUSR2) == -1)
					exit(EXIT_FAILURE);
			usleep(50);
		}
	}
	while (bit--)
	{
		kill(pid, SIGUSR2);
		usleep(50);
	}
}

static void	sig_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("Message received\n", 1);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3 || !(str_is_numeric(av[1])))
	{
		ft_putstr_fd("Invalid arguments!\n", 2);
		ft_putstr_fd("Usage: ./client [PID] [STR]\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	pid = ft_atoi(av[1]);
	send_msg(av[2], pid);
}
