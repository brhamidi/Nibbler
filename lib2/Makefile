# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/21 14:53:46 by bhamidi           #+#    #+#              #
#    Updated: 2018/05/28 13:34:20 by msrun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX= g++
NAME=sdl2.so
CXXFLAGS= -Werror -Wextra -Wall -std=c++11 -O2
LIBFLAGS= -framework sdl2
FILE_TYPE=cpp

SRC_PATH= ./
OBJ_PATH= ./
INCLUDE_PATH= ./

INCLUDES_PATH=./../includes

OBJ=Sdl2.o

INCLUDE=Sdl2.hpp

OBJS=$(addprefix $(OBJ_PATH), $(OBJ))
INCLUDES=$(addprefix $(INCLUDE_PATH), $(INCLUDE))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJ) -shared -fPIC -o $@ $(LIBFLAGS)

%.o: %.$(FILE_TYPE) $(INCLUDES) Makefile
	$(CXX) $(CXXFLAGS) -I $(INCLUDES_PATH) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)


re : fclean all

.PHONY: all fclean clean re
