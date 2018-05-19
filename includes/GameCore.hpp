/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:21:35 by msrun             #+#    #+#             */
/*   Updated: 2018/05/19 14:15:30 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMECORE_HPP
# define GAMECORE_HPP

#include <list>
#include <iostream>

#define RESET   "\033[0m"
#define BLACK   "\033[40m"      /* Black */
#define RED     "\033[41m"      /* Red */
#define GREEN   "\033[42m"      /* Green */
#define YELLOW  "\033[43m"      /* Yellow */
#define BLUE    "\033[44m"      /* Blue */
#define MAGENTA "\033[45m"      /* Magenta */
#define CYAN    "\033[46m"      /* Cyan */
#define WHITE   "\033[47m"      /* White */

struct Data
{
	long long	_score;
	short		_width;
	short		_height;
	short ** 	_map;

};

enum eDir
{
	Up = 0, Right, Down, Left, Exit = 32, Error = -1
};

enum eNum
{
	Blank = 0, Wall, Food, Snake, Head
};

class GameCore
{
	public:
		~GameCore(void);
		static GameCore &	getGame(short, short);
		bool	moveSnake(eDir);
		void	_printMap(void) const;
		Data &	getData(void);

	private:
		GameCore(short, short);
		GameCore(void);
		bool	_findPos(short, short, short, short);
		void	_buildTheWall(void);
		void	_popFood(void);
		void	_updateSnake(std::pair<short, short> &, eNum);

		std::list< std::pair< short, short > >	_snake;
		bool	_fed;
		eDir	_direction;
		Data	_data;
};

#endif
