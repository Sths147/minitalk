/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:38:28 by sithomas          #+#    #+#             */
/*   Updated: 2025/01/03 12:27:28 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
returns last element of list
*/

t_list	*ft_lstlast(t_list **lst)
{
	t_list	*current;

	if (!lst || !*lst)
		return (NULL);
	current = *lst;
	while (current->next)
		current = current->next;
	return (current);
}
/*
returns size of list
*/

size_t	ft_lstsize(t_list **lst)
{
	size_t	i;
	t_list	*current;

	if (!lst || !*lst)
		return (0);
	i = 1;
	current = *lst;
	while (current->next)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void	free_all(t_list **lst)
{
	t_list	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(lst);
		*lst = tmp;
	}
	free(lst);
}
