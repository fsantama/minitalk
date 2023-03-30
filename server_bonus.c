/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantama <fsantama@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:29:27 by fsantama          #+#    #+#             */
/*   Updated: 2023/03/30 17:15:05 by fsantama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

void	ft_handler(int i, siginfo_t *info, void *param)
{
	static int				bit = 0;
	static unsigned char	str = 0;

	(void)param;
	if (i == SIGUSR2)
		str = str + (1 << bit);
	bit++;
	if (bit == 8 && str)
	{
		write (1, &str, 1);
		bit = 0;
		str = 0;
	}
	else if (bit == 8 && str == 0)
	{
		kill(info->si_pid, SIGUSR1);
		bit = 0;
		str = 0;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
		ft_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}

int	main(void)
{
	struct sigaction	server;

	server.sa_sigaction = ft_handler;
	server.sa_flags = SA_SIGINFO;
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	write (1, "\n", 1);
	sigaction(SIGUSR1, &server, NULL);
	sigaction(SIGUSR2, &server, NULL);
	while (1)
		pause();
	return (0);
}
