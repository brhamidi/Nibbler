/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 15:01:12 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/31 18:19:34 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_HPP
# define NIBBLER_HPP

struct Data
{
	long long	_score;
	short		_width;
	short		_height;
	short ** 	_map;
};

enum eDir
{
	 Error = -1, Up, Right, Down, Left, Exit, Lib1, Lib2, Lib3, Space
};

enum eNum
{
	Blank = 0, Wall, Food, Snake, Head, Obstacle
};

#define RESET   "\033[0m"
#define BLACK   "\033[40m"      /* Black */
#define RED     "\033[41m"      /* Red */
#define GREEN   "\033[42m"      /* Green */
#define YELLOW  "\033[43m"      /* Yellow */
#define BLUE    "\033[44m"      /* Blue */
#define MAGENTA "\033[45m"      /* Magenta */
#define CYAN    "\033[46m"      /* Cyan */
#define WHITE   "\033[47m"      /* White */

#endif
