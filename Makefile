# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msrun <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/10 15:11:06 by msrun             #+#    #+#              #
#    Updated: 2018/05/21 16:21:50 by msrun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX= g++
NAME=nibbler
CXXFLAGS= -Werror -Wextra -Wall -std=c++11 -O2
FILE_TYPE=cpp

SRC_PATH= srcs/
OBJ_PATH= obj/
INCLUDE_PATH= includes/

OBJ=GameCore.o main.o

INCLUDE=GameCore.hpp IGraphicLib.hpp

OBJS=$(addprefix $(OBJ_PATH), $(OBJ))
INCLUDES=$(addprefix $(INCLUDE_PATH), $(INCLUDE))

LIB1_PATH=lib1/
LIB1_NAME=ncurses.so
SYM1=lib1.so

all: $(NAME) MAKELIBS

$(NAME): $(OBJ_PATH) $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $@
	@ln -fs $(LIB1_PATH)$(LIB1_NAME) $(SYM1)

$(OBJ_PATH)%.o: $(SRC_PATH)%.$(FILE_TYPE) $(INCLUDES) Makefile
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

MAKELIBS:
	@make -C $(LIB1_PATH)

$(OBJ_PATH):
	@mkdir -p $@

clean:
	make clean -C $(LIB1_PATH)
	rm -f $(SYM1)
	rm -f $(OBJS)

fclean : clean
	make fclean -C $(LIB1_PATH)
	rm -f $(NAME)

re : fclean all

.PHONY: all fclean clean re
