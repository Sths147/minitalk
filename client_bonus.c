/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:31:51 by sithomas          #+#    #+#             */
/*   Updated: 2025/01/03 13:31:13 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int				mypid(char *str);
static void				sendbyte(unsigned char c, int PID, size_t size);
static void				handler(int signal);
volatile sig_atomic_t	g_check;

/*
Client behaviour:
	1. Converts PID (argv[1]) into int and checks if error
	2. For each char of the message (argv[2]), converts each bit of each
	char into SIGSUR1 (if 1) or SIGSUR2 (if 0)
*/

int	main(int argc, char **argv)
{
	int		pid;
	size_t	i;

	if (argc != 3)
	{
		write(1, "Wrong number of arguments :(\n", 30);
		exit(1);
	}
	pid = mypid(argv[1]);
	if (pid < 0)
		exit(1);
	g_check = 0;
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	i = 0;
	while (argv[2][i])
		sendbyte(argv[2][i++], pid, 8);
	sendbyte('\0', pid, 8);
	exit(0);
	return (0);
}
/*
Converts the argv[1] (PID) into an int. Returns an error if invalid format
or if PID is wrong
*/

static int	mypid(char *str)
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
for every bit of the character, sends a :
	* SIGUSR1 if bit == 1
	* SIGUSR2 else (bit == 0)
Checks if server sends back a signal
*/

static void	sendbyte(unsigned char c, int pid, size_t size)
{
	unsigned char	tmp;
	size_t			timeoutchecker;

	while (size > 0)
	{
		tmp = c;
		g_check = 0;
		if (((tmp >> (size - 1)) & 1) == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		timeoutchecker = 0;
		while (!g_check)
		{
			usleep(100);
			timeoutchecker++;
			if (timeoutchecker > 30)
				exit(1);
		}
		size--;
	}
}

/*
Handler to send a signal to client to let him know the bit is received
if SIGUSR2 received, indicates server received well the whole message
*/

static void	handler(int signal)
{
	if (signal == SIGUSR1)
		g_check = 1;
	if (signal == SIGUSR2)
		write(1, "Successful reception by server\n", 31);
}
