/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:21:35 by msrun             #+#    #+#             */
/*   Updated: 2018/05/17 12:38:23 by bhamidi          ###   ########.fr       */
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

enum eNum
{
	Blank, Wall, Snake, Food
};

class GameCore
{
	public:
		~GameCore(void);
		static GameCore const &	getGame(short, short);

	private:
		GameCore(short, short);
		GameCore(void);
		bool	_findPos(short, short, short, short);
		void	_buildTheWall(void);
		void	_popFood(void);
		void	_printMap(void) const;

		std::list< std::pair< short, short > >	_snake;
		std::list< std::pair< short, short > >	_food;
		Data	_data;
};

#endif
