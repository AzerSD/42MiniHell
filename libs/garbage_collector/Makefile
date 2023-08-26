# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 03:36:39 by asioud            #+#    #+#              #
#    Updated: 2023/08/26 23:00:57 by lhasmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra

LIB_NAME = garbage_collector.a


SRC_FILES = memory.c memory_utils.c
OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(LIB_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME): $(OBJ_FILES)
	ar rcs $@ $(OBJ_FILES)

clean:
	rm -rf $(OBJ_FILES)

fclean: clean
	rm -rf $(LIB_NAME)

.PHONY: all clean
