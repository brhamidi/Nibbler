# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/21 14:53:46 by bhamidi           #+#    #+#              #
#    Updated: 2018/05/31 18:56:01 by bhamidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX				= g++
NAME			= sound.so
CXXFLAGS		= -Werror -Wextra -Wall -std=c++11 -O2
LIBFLAGS 		=  -L ~/.brew/lib -lsfml-audio
INCLUDES_PATH 	= -I ~/.brew/include

FILE_TYPE=cpp

SRC_PATH= ./
OBJ_PATH= ./


OBJ = Sound.o

INCLUDE=Sound.hpp

OBJS=$(addprefix $(OBJ_PATH), $(OBJ))
INCLUDES=$(addprefix $(INCLUDE_PATH), $(INCLUDE))

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -shared -fPIC -o $@ $(LIBFLAGS) -I../includes

%.o: %.$(FILE_TYPE) $(INCLUDES) Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDES_PATH) -c $< -o $@ -I../includes

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)


re : fclean all

.PHONY: all fclean clean re
