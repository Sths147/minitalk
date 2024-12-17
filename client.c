/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:31:51 by sithomas          #+#    #+#             */
/*   Updated: 2024/12/17 19:29:57 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	getPID(char *str);
static void	send_char(unsigned char c, int PID);
static void handler(int signal);
static volatile int check;

/*
Program behaviour:
	1. Converts argv[1] into int
	2. For each char of argv[2], converts each bit of char into SIGSUR1 (if 1) 
	or SIGSUR2 (if 0)
*/

int	main(int argc, char **argv)
{
	int		PID;
	size_t	i;
	
	if (argc != 3)
	{
		write(1, "Wrong number of arguments :(\n", 30);
		return (-1);
	}
	PID = getPID(argv[1]);
	printf("%d\n", PID);
	if (PID < 0)
		return (-1);
	i = 0;
	check = 0;
	signal(SIGUSR1, handler);
	while (argv[2][i])
		send_char(argv[2][i++], PID);
	send_char('\0', PID);
	write(1, "sent\n", 5);
	exit(0);
	return (0);
}
/*
Converts a char * into an int. Returns an error if char != digit
*/

static void handler(int signal)
{
	if (signal == SIGUSR1)
		check = 1;
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
/*
Cuts char into bits and sends signal depending on binary (SIGSUR1 if 1 and SIGSUR2 if 0)
*/

static void	send_char(unsigned char c, int PID)
{
	size_t	i;
	size_t	sizeByte;

	i = 0;
	sizeByte = 8;
	while (i < 8)
	{
		check = 0;
		if (((c >> i) & 1) == 1)
			kill(PID, SIGUSR1);
		else
			kill(PID, SIGUSR2);
		usleep(100);
		while (check == 0)
			pause();
		i++;
	}
}