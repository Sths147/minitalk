# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 16:23:34 by sithomas          #+#    #+#              #
#    Updated: 2025/01/03 12:28:10 by sithomas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

SRC_SERVER = server.c \
			server_2.c \

SRC_CLIENT = client.c \

SRC_SERVER_BONUS = server_bonus.c \
				server_2_bonus.c \

SRC_CLIENT_BONUS = client_bonus.c \

INC = minitalk.h \

O_CLIENT = $(SRC_CLIENT:.c=.o)

O_SERVER = $(SRC_SERVER:.c=.o)

O_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)

O_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)

all: server client

bonus: server_bonus client_bonus

server: $(O_SERVER)
	$(CC) $(CFLAGS) $(O_SERVER) -o $@

client: $(O_CLIENT)
	$(CC) $(CFLAGS) $(O_CLIENT) -o $@

server_bonus: $(O_SERVER_BONUS)
	$(CC) $(CFLAGS) $(O_SERVER_BONUS) -o $@

client_bonus: $(O_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(O_CLIENT_BONUS) -o $@

%.o: %.c $(INC) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f client server client_bonus server_bonus

re : fclean all

.PHONY: all clean fclean re