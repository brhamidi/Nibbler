# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/21 14:53:46 by bhamidi           #+#    #+#              #
#    Updated: 2018/05/21 16:23:28 by msrun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CXX= g++
NAME=ncurses.so
CXXFLAGS= -Werror -Wextra -Wall -std=c++11 -O2

OBJ=Ncurses.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -shared -fPIC -o $@ -lncurses -std=c++11

%.o: %.cpp Ncurses.hpp Makefile
	$(CXX) $(CXXFLAGS) -I./../includes -c $< -o $@

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)


re : fclean all

.PHONY: all fclean clean re
