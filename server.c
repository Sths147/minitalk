/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:31:51 by sithomas          #+#    #+#             */
/*   Updated: 2024/12/13 18:21:16 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	getPID(char *str);
static void	handler(int signal);

int	main(int argc, char **argv)
{
	struct sigaction	act;
	int					PID;
	
	if (argc != 3)
	{
		write(1, "Wrong number of arguments :(\n", 30);
		return (-1);
	}
	PID = getPID(argv[1]);
	if (PID < 0)
		return (-1);
	/*
	I want to modify the effect of SIGUR1 signal with sigaction to make it transmit argv[2];
	*/
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	/*
	I want to send SIGUR1 Signal to the PID in argv[1];
	*/
	kill(PID, SIGUSR1);
	write(1, "sent\n", 5);
}

static void	handler(int signal)
{
	if (signal == SIGUSR1)
	{
		write(1, "Coucou c'est moi le serveur\n", 28);
		exit(0);
	}
	exit(1);
}

static int	getPID(char *str)
{
	size_t	i;
	int		result;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 58)
		{
			printf("First arg is not PID, pleade put PID as first argument and message as second\n");
			return (-1);
		}
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result);
}