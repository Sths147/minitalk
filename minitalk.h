/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:33:04 by sithomas          #+#    #+#             */
/*   Updated: 2024/12/20 13:17:51 by sithomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_itoa(int n);
size_t	ft_atoi_minitalk(const char *nptr);

typedef struct s_list
{
	char s[2];
	struct s_list	*next;
}				t_list;

#endif