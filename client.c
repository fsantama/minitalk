/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantama <fsantama@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:25:30 by fsantama          #+#    #+#             */
/*   Updated: 2023/03/28 17:40:26 by fsantama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
// #include <stdio.h>

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
	if (str[i] == 45)
		sign *= -1;
	if (str[i] == 43 || sign == -1)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		b = (str[i] - '0') + (b * 10);
		i++;
	}
	return (sign * b);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		write(1, "client: invalid arguments\n", 27);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	ft_send_bytes(pid, argv[2]);
	ft_send_bytes(pid, "\n\0");
	return (0);
}
