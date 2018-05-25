/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:21:35 by msrun             #+#    #+#             */
/*   Updated: 2018/05/25 16:24:05 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMECORE_HPP
# define GAMECORE_HPP

#include <list>
#include <iostream>
#include "Nibbler.hpp"

struct snakeData
{
	bool	fed;
	eDir	direction;
	std::list < std::pair <short, short > > snake;
};

class GameCore
{
	public:
		~GameCore(void);
		static GameCore &	getGame(short, short, unsigned char);
		bool	moveSnake(eDir*);
		void	_printMap(void) const;
		Data &	getData(void);

	private:
		GameCore(short, short, unsigned char, bool);
		GameCore(void);
		bool	_movePlayer(eDir, snakeData &);
		void	_initSnake(snakeData);
		bool	_findPos(short, short, short, short, eNum);
		void	_buildTheWall(void);
		void	_popElem(eNum);
		void	_updateSnake(std::pair<short, short> &, eNum);

		bool		_p2;
		snakeData	_snake;
		snakeData	_snake2;
		Data		_data;
};

#endif
