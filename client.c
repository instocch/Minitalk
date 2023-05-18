/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstocche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:52:12 by mstocche          #+#    #+#             */
/*   Updated: 2023/05/17 17:57:25 by mstocche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "printf/ft_printf.h"
#include "libft/libft.h"

void	wake_up(int sig)
{
	sig = 0;
	return ;
}

void	send_str_len(unsigned int str_len, int pid)
{
	unsigned int	mask;
	int				i;

	i = 31;
	while (i >= 0)
	{
		mask = (str_len >> i) & 1;
		if (mask == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		pause();
	}
}

void	send_str(char *str, int pid)
{
	int				i;
	int				j;
	unsigned int	mask;

	i = 0;
	while (str[i] != '\0')
	{
		j = 7;
		while (j >= 0)
		{
			mask = (str[i] >> j) & 1;
			if (mask == 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			j--;
			pause();
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int				server_pid;
	unsigned int	len;

	if (argc != 3)
	{
		write(1, "Usage: PID STRING", 19);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, wake_up);
	server_pid = ft_atoi(argv[1]);
	len = (unsigned int)ft_strlen(argv[2]);
	send_str_len(len, server_pid);
	send_str(argv[2], server_pid);
    write(1, "Receive message", 15);
}
