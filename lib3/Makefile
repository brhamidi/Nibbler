# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/21 14:53:46 by bhamidi           #+#    #+#              #
#    Updated: 2018/05/28 13:25:46 by msrun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX				= g++
NAME			= sfml.so
CXXFLAGS		= -Werror -Wextra -Wall -std=c++11 -O2
LIBFLAGS 		=  -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics
INCLUDES_PATH 	= -I ~/.brew/include -I./../includes

FILE_TYPE=cpp

SRC_PATH= ./
OBJ_PATH= ./
INCLUDE_PATH= ./

OBJ = Sfml.o

INCLUDE=Sfml.hpp

OBJS=$(addprefix $(OBJ_PATH), $(OBJ))
INCLUDES=$(addprefix $(INCLUDE_PATH), $(INCLUDE))

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -shared -fPIC -o $@ $(LIBFLAGS)

%.o: %.$(FILE_TYPE) $(INCLUDES) Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDES_PATH) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)


re : fclean all

.PHONY: all fclean clean re
