# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/21 14:53:46 by bhamidi           #+#    #+#              #
#    Updated: 2018/05/23 15:38:39 by bhamidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CXX				= g++
NAME			= sfml.so
CXXFLAGS		= -Werror -Wextra -Wall -std=c++11 -O2
LIBFLAGS 		=  -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio
INCLUDES_PATH 	= -I ~/.brew/include -I./../includes

OBJ = Sfml.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -shared -fPIC -o $@ $(LIBFLAGS)

%.o: %.cpp Makefile Sfml.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDES_PATH) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)


re : fclean all

.PHONY: all fclean clean re
