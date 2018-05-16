# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msrun <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/10 15:11:06 by msrun             #+#    #+#              #
#    Updated: 2018/05/10 15:53:43 by msrun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= clang++
NAME= Abstract
CFLAGS= -Werror -Wextra -Wall -std=c++11
FILE_TYPE=cpp

SRC_PATH= srcs/
OBJ_PATH= obj/
INCLUDE_PATH= includes/
MAKEFILE= Makefile

OBJ= 

INCLUDE= 

OBJS=$(addprefix $(OBJ_PATH), $(OBJ))
INCLUDES=$(addprefix $(INCLUDE_PATH), $(INCLUDE))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.$(FILE_TYPE) $(INCLUDES) $(MAKEFILE)
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all fclean clean re
