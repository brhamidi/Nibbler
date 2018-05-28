# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/21 14:53:46 by bhamidi           #+#    #+#              #
#    Updated: 2018/05/28 13:42:24 by msrun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX= g++
NAME=ncurses.so
CXXFLAGS= -Werror -Wextra -Wall -std=c++11 -O2
FILE_TYPE=cpp

SRC_PATH= ./
OBJ_PATH= ./
INCLUDE_PATH= ./

INCLUDES_GAME=../includes/IGraphicLib.hpp	../includes/Nibbler.hpp

OBJ=Ncurses.o

INCLUDE=Ncurses.hpp

OBJS=$(addprefix $(OBJ_PATH), $(OBJ))
INCLUDES=$(addprefix $(INCLUDE_PATH), $(INCLUDE))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJ) -shared -fPIC -o $@ -lncurses -std=c++11

%.o: %.$(FILE_TYPE) $(INCLUDES) $(INCLUDES_GAME) Makefile
	$(CXX) $(CXXFLAGS) -I./../includes -c $< -o $@

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)


re : fclean all

.PHONY: all fclean clean re
