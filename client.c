/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:31:55 by sithomas          #+#    #+#             */
/*   Updated: 2024/12/13 18:21:02 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(void)
{
	
	printf("%d\n", getpid());
	while (1)
	{
		pause();
		signal(SIGUSR1, SIG_IGN);
	}
	exit(0);
	return (0);
}