/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:31:51 by sithomas          #+#    #+#             */
/*   Updated: 2024/12/19 18:01:39 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int						getPID(char *str);
static int						sendByte(size_t c, int PID, size_t size);
static void						handler(int signal);
static size_t					ft_strlen_minitalk(char *s);
static volatile sig_atomic_t	check;

/*
Program behaviour:
	1. Converts PID (argv[1]) into int and checks if error
	2. For each char of the massage (argv[2]), converts each bit of each
	char into SIGSUR1 (if 1) or SIGSUR2 (if 0)
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
	if (PID < 0)
		return (-1);
	check = 0;
	signal(SIGUSR1, handler);
	i = 0;
	printf("%zu\n", ft_strlen_minitalk(argv[2]));
	sendByte(ft_strlen_minitalk(argv[2]), PID, 64);
	printf("done\n");	
	usleep(100);
	i = 0;
	while (argv[2][i])
		sendByte(argv[2][i++], PID, 8);
	sendByte('\0', PID, 8);
	write(1, "sent\n", 5);
	exit(0);
	return (0);
}
/*
Converts the argv[1] (PID) into an int. Returns an error if invalid format
or if PID is wrong
*/

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
			write(1, "Invalid PID :(\n", 14);
			return (-1);
		}
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	if (kill(result, 0) == -1)
	{
		write(1, "Invalid PID :(\n", 14);
		return (-1);
	}
	return (result);
}
/*
Sends the len of argv[2] to the server
Checks if server sends back a signal 
*/

static int	sendByte(size_t len, int PID, size_t size)
{
	size_t			tmp;
	// size_t			size;
	size_t			timeOutChecker;
	
	while (size > 0)
	{
		tmp = len;
		check = 0;
		if (((tmp >> (size - 1)) & 1) == 1)
			kill(PID, SIGUSR1);
		else
			kill(PID, SIGUSR2);
		timeOutChecker = 0;
		while (check == 0)
		{
			usleep(10000);
			timeOutChecker++;
			if (timeOutChecker > 30)
				return (-1);
		}
		size--;
	}
	return (0);
}

/*
Handler to send a signal to client to let him know the bit is received
*/

static void	handler(int signal)
{
	if (signal == SIGUSR1)
		check = 1;
}

/*
Calculates length of str
*/
static size_t	ft_strlen_minitalk(char *s)
{
	size_t	i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}