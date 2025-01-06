# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sithomas <sithomas@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 16:23:34 by sithomas          #+#    #+#              #
#    Updated: 2025/01/06 14:08:41 by sithomas         ###   ########.fr        #
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

all: git ft_printf server client

bonus: git ft_printf server_bonus client_bonus

git:
	git submodule update --init

ft_printf:
	$(MAKE) -C printf

server: $(O_SERVER)
	cp printf/*.o .
	$(CC) $(CFLAGS) *.o -o $@

client: $(O_CLIENT)
	$(CC) $(CFLAGS) $(O_CLIENT) -o $@

server_bonus: $(O_SERVER_BONUS)
	cp printf/*.o .
	$(CC) $(CFLAGS) *.o -o $@

client_bonus: $(O_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(O_CLIENT_BONUS) -o $@

%.o: %.c $(INC) Makefile minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C printf
	rm -f *.o

fclean: clean
	rm -f client server client_bonus server_bonus printf/libftprintf.a

re : fclean all

.PHONY: all clean fclean re