/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantama <fsantama@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:25:30 by fsantama          #+#    #+#             */
/*   Updated: 2023/03/30 17:18:30 by fsantama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_final_message(pid_t pid)
{
	int	count;

	count = 0;
	while (count != 8)
	{
		kill(pid, SIGUSR1);
		usleep(100);
		count++;
	}
}

void	ft_handler(int i)
{
	if (i == SIGUSR1)
		write(1, "Message received by server.\n", 28);
}

void	ft_send_bytes(pid_t pid, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		count = 0;
		while (count != 8)
		{
			if ((str[i] >> (count)) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
			count++;
		}
		i++;
	}
	ft_final_message(pid);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	b;

	i = 0;
	sign = 1;
	b = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		b = b * 10 + str[i] - '0';
		i++;
	}
	return (b * sign);
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		write(1, "Usage: ./client [server PID] [str to send]\n", 43);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, ft_handler);
	ft_send_bytes(pid, argv[2]);
	return (0);
}
