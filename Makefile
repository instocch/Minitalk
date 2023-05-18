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

NAME = dependencies server client
SRCS = server.c client.c
OBJ = $(SRCS:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror

LIBFT = libft/
PRINTF = printf/

all: $(NAME)

bonus: $(NAME)

dependencies:
	make all -C $(LIBFT)
	make all -C $(PRINTF)

server: server.o dependencies
	$(CC) -L$(LIBFT) -L$(PRINTF) -o $@ $< -lft -lftprintf


client: client.o dependencies
	$(CC) -L$(LIBFT) -L$(PRINTF) -o $@ $< -lft -lftprintf

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
