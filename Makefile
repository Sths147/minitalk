# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 16:23:34 by sithomas          #+#    #+#              #
#    Updated: 2024/12/17 19:14:49 by sithomas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

SRC_SERVER = server.c

SRC_CLIENT = client.c

INC = minitalk.h \

O_CLIENT = $(SRC_CLIENT:.c=.o)

O_SERVER = $(SRC_SERVER:.c=.o)

all: server client

server: $(O_SERVER)
	$(CC) $(CFLAGS) $(O_SERVER) -o $@

client: $(O_CLIENT)
	$(CC) $(CFLAGS) $(O_CLIENT) -o $@

%.o: %.c $(INC) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(O_SERVER) $(O_CLIENT)

fclean: clean
	rm -f client server

re : fclean all

.PHONY: all clean fclean re