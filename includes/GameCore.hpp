/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:21:35 by msrun             #+#    #+#             */
/*   Updated: 2018/05/18 13:01:24 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMECORE_HPP
# define GAMECORE_HPP

#include <list>
#include <iostream>

struct Data
{
	long long								_score;
	short									_width;
	short									_height;
	short ** 								_map;

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

enum eNum
{
	Blank, Wall, Snake, Food
};

class GameCore
{
	public:
		~GameCore(void);
		static GameCore &	getGame(short, short);
		bool	moveSnake(int);
		void	_printMap(void) const;

	private:
		GameCore(short, short);
		GameCore(void);
		bool	_findPos(short, short, short, short);
		void	_buildTheWall(void);
		void	_popFood(void);
		void	_updateSnake(std::pair<short, short> &, bool);

		std::list< std::pair< short, short > >	_snake;
		std::list< std::pair< short, short > >	_food;
		bool	_fed;
		int		_direction;
		Data	_data;
};

#endif
