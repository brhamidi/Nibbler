# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/21 14:53:46 by bhamidi           #+#    #+#              #
#    Updated: 2018/05/29 16:11:19 by bhamidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX				= g++
NAME			= sdl2.so
CXXFLAGS		= -Werror -Wextra -Wall -std=c++11 -O2
LIBFLAGS		= -L /Users/bhamidi/.brew/lib -lSDL_ttf -lSDL2
INCLUDES_PATH	= /Users/bhamidi/.brew/include -I ./../includes
FILE_TYPE		= cpp

SRC_PATH= ./
OBJ_PATH= ./

INCLUDES_GAME	=../includes/IGraphicLib.hpp	../includes/Nibbler.hpp

OBJ=Sdl2.o

INCLUDE=Sdl2.hpp

OBJS=$(addprefix $(OBJ_PATH), $(OBJ))
INCLUDES=$(addprefix $(INCLUDE_PATH), $(INCLUDE))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJ) -shared -fPIC -o $@ $(LIBFLAGS)

%.o: %.$(FILE_TYPE) $(INCLUDES) $(INCLUDES_GAME) Makefile
	$(CXX) $(CXXFLAGS) -I $(INCLUDES_PATH) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)


re : fclean all

.PHONY: all fclean clean re
