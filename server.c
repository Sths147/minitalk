/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:31:55 by sithomas          #+#    #+#             */
/*   Updated: 2024/12/19 19:36:57 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
Client behaviour:
	1. Prints PID
	2. Listens to signals, if receives a signal, then reconstitutes chars and prints;
*/

static void		handler(int signal, siginfo_t *info, void *context);
static char		*result;
static size_t	len;

int	main(void)
{
	struct sigaction 	act;
	
	printf("%d\n---------------PRINT AREA----------------\n\n", getpid());
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{	
		if (len != 0)
		{	
			result = malloc((len + 1) * sizeof(char));
			if (!result)
				exit(1);
			result[len] = 'Z';
			while(result[len] == 'Z')
				pause();
			printf("Result: %s\n", result);
			free(result);
			len = 0;
			continue;
		}
	}
	return (0);
}
static void	handler(int signal, siginfo_t *info, void *context)
{
	static size_t				c;
	static size_t				bits;
	static size_t				index;
	static size_t				islen;

	(void)context;
	c = c << 1;
	if (signal == SIGUSR1)
		c |= 1;
	bits++;
	if (islen == 0 && bits == 64)
	{	
		len = c;
		c = 0;
		bits = 0;
		islen = 1;
	}
	if (islen == 1 && bits == 8)
	{	
		result[index] = c;
		index++;
		if (result[index - 1] == '\0')
		{	
			index = 0;
			islen = 0;
		}
		bits = 0;
		c = '\0';
	}
	kill(info->si_pid, SIGUSR1);
}
