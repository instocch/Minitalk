# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstocche <mstocche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 14:37:01 by mstocche          #+#    #+#              #
#    Updated: 2023/05/17 17:23:54 by mstocche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server client
SRCS = server.c client.c
OBJ = $(SRCS:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror

LIBFT = libft/
PRINTF = printf/

all: $(NAME)

bonus: $(NAME)

server: server.o 
	make -C $(LIBFT) 
	make -C $(PRINTF)
	$(CC) -o $@ $< ./libft/libft.a -Llibft -lft ./printf/libftprintf.a -Lprintf -lft
	

client: client.o
	$(CC) -o $@ $< ./libft/libft.a Llibft -lft ./printf/libftprintf.a -Lprintf -lft

%.o: %.c
	$(CC) -c $(FLAGS) $?


clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT)
	make clean -C $(PRINTF)
	
fclean: clean
	make fclean -C $(LIBFT)
	make fclean -C $(PRINTF)
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus libft clean fclean re
