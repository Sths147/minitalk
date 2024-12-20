/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:31:55 by sithomas          #+#    #+#             */
/*   Updated: 2024/12/20 13:53:30 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
Client behaviour:
	1. Prints PID
	2. Listens to signals, if receives a signal, then reconstitutes chars and prints;
*/

static void		handler(int signal, siginfo_t *info, void *context);
static char		*jointhisfuckinglist(t_list **lst, size_t size);
static size_t	ft_lstsize(t_list **lst);
static void	ft_lstadd_back(t_list **lst, char c);

t_list				**lst;

int	main(void)
{
	struct sigaction 	act;
	char				*result;
	size_t				size;

	printf("%d\n---------------PRINT AREA----------------\n\n", getpid());
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{	
		if (lst)
			while ((*lst)->s[0] != '\0')
				pause();
		size = 0;
		size = ft_lstsize(lst);
		if (size != 0)
		{	
			printf("%zu\n", size);
			result = jointhisfuckinglist(lst, size);
			if (!result)
				exit(1);
			printf("%s\n", result);
		}
	}
	return (0);
}
static void	handler(int signal, siginfo_t *info, void *context)
{
	static size_t				c;
	static size_t				bits;

	(void)context;
	c = c << 1;
	if (signal == SIGUSR1)
		c |= 1;
	bits++;
	if (bits == 8)
	{	
		ft_lstadd_back(lst, c);
	}
	kill(info->si_pid, SIGUSR1);
}
static void	ft_lstadd_back(t_list **lst, char c)
{
	t_list	*last;
	t_list	*new;
	
	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->s[0] = c;
	new->s[1] = '\0';
	new->next = NULL;
	if (!lst)
		*lst = new;
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}
static size_t	ft_lstsize(t_list **lst)
{
	size_t	i;
	
	i = 1;
	if (!lst)
		return (0);
	while ((*lst)->next)
		i++;
	return (i);
}

static char	*jointhisfuckinglist(t_list **lst, size_t size)
{
	char	*result;
	t_list	*tmp;
	size_t	i;

	result = malloc(size + 1);
	if (!result)
		return (NULL);
	i = 0;
	while ((*lst)->next)
	{
		result[i] = (*lst)->s[0];
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
		i++;
	}
	free(lst);
	return (result);
}