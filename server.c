/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:31:55 by sithomas          #+#    #+#             */
/*   Updated: 2024/12/18 16:05:04 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
Client behaviour:
	1. Prints PID
	2. Listens to signals, if receives a signal, then reconstitutes chars and prints;
*/

static void	handler(int signal, siginfo_t *info, void *context);
static char	**result;

int	main(void)
{
	struct sigaction 	act;
	size_t				len;
	
	printf("%d\n---------------PRINT AREA----------------\n\n", getpid());
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	result = malloc((sizeof(size_t) + 1) * sizeof(char));
	if (result)
		exit(1);
	while (*result != '\0')
		pause();
	len = ft_atoi(result);
	while (1)
	{	
		free(result);
		result = malloc((len + 1) * sizeof(char));
		if (!result)
			exit(1);
		while(*result != '\0')
			pause();
	}
	return (0);
}
static void	handler(int signal, siginfo_t *info, void *context)
{
	static size_t				c;
	static size_t				bytes;

	(void)context;
	if (!c)
		c = 0;
	if (!bytes)
		bytes = 0;
	c = c << 1;
	if (signal == SIGUSR1)
		c |= 1;
	bytes++;
	if (bytes == 8)
	{	
		if (c == '\0')
			write(1, "\n", 1);
		else 
			write(1, &c, 1);
		bytes = 0;
		c = '\0';
	}
	kill(info->si_pid, SIGUSR1);
}
