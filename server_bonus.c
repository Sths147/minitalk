/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:31:55 by sithomas          #+#    #+#             */
/*   Updated: 2025/01/03 12:27:15 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
Client behaviour:
	1. Prints PID
	2. Listens to signals, if receives a signal, then
	reconstitutes chars and prints;
*/

static void	handler(int signal, siginfo_t *info, void *context);
static char	*get_result(t_list **lst, size_t size);
static void	ft_lstadd_back(t_list **lst, char c);
static void	setup_handler(void);

t_list		**g_lst;

int	main(void)
{
	char	*result;
	size_t	size;

	setup_handler();
	while (1)
	{
		g_lst = malloc(sizeof(t_list *));
		if (!g_lst)
			exit(1);
		*g_lst = NULL;
		while (!(*g_lst) || ft_lstlast(g_lst)->s[0] != '\0')
			pause();
		size = ft_lstsize(g_lst);
		if (size > 0)
		{
			result = get_result(g_lst, size);
			if (!result)
				exit(1);
			printf("%s\n", result);
			free(result);
		}
	}
	return (0);
}

static void	setup_handler(void)
{
	struct sigaction	act;

	printf("%d\n---------------PRINT AREA----------------\n\n", getpid());
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

static void	handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static size_t			bits = 0;

	(void)context;
	c = c << 1;
	if (signal == SIGUSR1)
		c |= 1;
	bits++;
	if (bits == 8)
	{
		ft_lstadd_back(g_lst, c);
		if (c == '\0')
			kill(info->si_pid, SIGUSR2);
		bits = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

static void	ft_lstadd_back(t_list **lst, char c)
{
	t_list	*last;
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
	{	
		free_all(lst);
		return (exit(1));
	}
	new->s[0] = c;
	new->s[1] = '\0';
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

static char	*get_result(t_list **lst, size_t size)
{
	char	*result;
	t_list	*tmp;
	size_t	i;

	if (!lst || !*lst)
		return (NULL);
	result = malloc(size + 1);
	if (!result)
	{	
		free_all(lst);
		return (NULL);
	}
	i = 0;
	while (*lst && (*lst)->s[0] != '\0')
	{
		result[i] = (*lst)->s[0];
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
		i++;
	}
	result[i] = '\0';
	free(*lst);
	free(lst);
	return (result);
}

