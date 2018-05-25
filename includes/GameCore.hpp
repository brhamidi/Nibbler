/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:21:35 by msrun             #+#    #+#             */
/*   Updated: 2018/05/25 17:47:31 by msrun            ###   ########.fr       */
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
		bool	moveSnake(eDir*);
		static GameCore &	getGame(short, short, short);
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

		bool		_fed;
		eDir		_direction;
		bool		_p2;
		snakeData	_snake;
		snakeData	_snake2;
		Data		_data;
};

#endif
