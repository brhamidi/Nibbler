# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msrun <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/10 15:11:06 by msrun             #+#    #+#              #
#    Updated: 2018/05/31 18:19:19 by bhamidi          ###   ########.fr        #
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

INCLUDE=GameCore.hpp IGraphicLib.hpp Nibbler.hpp

OBJS=$(addprefix $(OBJ_PATH), $(OBJ))
INCLUDES=$(addprefix $(INCLUDE_PATH), $(INCLUDE))

LIB1_PATH=lib1/
LIB1_NAME=ncurses.so
SYM1=lib1.so

LIB2_PATH=lib2/
LIB2_NAME=sdl2.so
SYM2=lib2.so

LIB3_PATH=lib3/
LIB3_NAME=Sfml.so
SYM3=lib3.so

LIB4_PATH=lib4/
LIB4_NAME=Glfw.so
SYM4=lib4.so

LIB5_PATH=lib5/
LIB5_NAME=sound.so
SYM5=lib5.so


all: $(NAME) MAKELIBS

$(NAME): $(OBJ_PATH) $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $@ -Wl,-rpath,$$HOME/.brew/lib
	@ln -fs $(LIB1_PATH)$(LIB1_NAME) $(SYM1)
	@ln -fs $(LIB2_PATH)$(LIB2_NAME) $(SYM2)
	@ln -fs $(LIB3_PATH)$(LIB3_NAME) $(SYM3)
	@ln -fs $(LIB4_PATH)$(LIB4_NAME) $(SYM4)
	@ln -fs $(LIB5_PATH)$(LIB5_NAME) $(SYM5)

$(OBJ_PATH)%.o: $(SRC_PATH)%.$(FILE_TYPE) $(INCLUDES) Makefile
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

MAKELIBS:
	@make -C $(LIB1_PATH)
	@make -C $(LIB2_PATH)
	@make -C $(LIB3_PATH)
	@make -C $(LIB4_PATH)
	@make -C $(LIB5_PATH)

$(OBJ_PATH):
	@mkdir -p $@

clean:
	make clean -C $(LIB1_PATH)
	make clean -C $(LIB2_PATH)
	make clean -C $(LIB3_PATH)
	make clean -C $(LIB4_PATH)
	make clean -C $(LIB5_PATH)
	rm -f $(SYM1)
	rm -f $(SYM2)
	rm -f $(SYM3)
	rm -f $(SYM4)
	rm -f $(SYM5)
	rm -f $(OBJS)

fclean : clean
	make fclean -C $(LIB1_PATH)
	make fclean -C $(LIB2_PATH)
	make fclean -C $(LIB3_PATH)
	make fclean -C $(LIB4_PATH)
	make fclean -C $(LIB5_PATH)
	rm -f $(NAME)

re : fclean all

.PHONY: all fclean clean re
