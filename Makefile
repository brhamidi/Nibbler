# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msrun <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/10 15:11:06 by msrun             #+#    #+#              #
#    Updated: 2018/05/16 17:18:40 by bhamidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= clang++
NAME=nibbler
CFLAGS= -Werror -Wextra -Wall -std=c++11 -O2
FILE_TYPE=cpp

SRC_PATH= srcs/
OBJ_PATH= obj/
INCLUDE_PATH= includes/

OBJ=GameCore.o main.o

INCLUDE=GameCore.hpp

OBJS=$(addprefix $(OBJ_PATH), $(OBJ))
INCLUDES=$(addprefix $(INCLUDE_PATH), $(INCLUDE))

all: $(NAME)

$(NAME): setup $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.$(FILE_TYPE) $(INCLUDES) Makefile
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

setup:
	@mkdir -p obj

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all fclean clean re
