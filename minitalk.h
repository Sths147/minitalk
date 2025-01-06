/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:33:04 by sithomas          #+#    #+#             */
/*   Updated: 2025/01/06 13:25:29 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include "printf/ft_printf.h"

typedef struct s_list
{
	char			s[2];
	struct s_list	*next;
}				t_list;

t_list	*ft_lstlast(t_list **lst);
size_t	ft_lstsize(t_list **lst);
void	free_all(t_list **lst);

#endif