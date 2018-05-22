# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/21 14:53:46 by bhamidi           #+#    #+#              #
#    Updated: 2018/05/22 12:20:58 by bhamidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CXX			= g++
NAME		= sdl2.so
CXXFLAGS	= -Werror -Wextra -Wall -std=c++11 -O2
LIBFLAGS 	= -framework sdl2

OBJ 		= Sdl2.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -shared -fPIC -o $@ $(LIBFLAGS)

%.o: %.cpp Makefile Sdl2.hpp
	$(CXX) $(CXXFLAGS) -I./../includes -c $< -o $@

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)


re : fclean all

.PHONY: all fclean clean re
