/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:21:35 by msrun             #+#    #+#             */
/*   Updated: 2018/05/31 18:49:44 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMECORE_HPP
# define GAMECORE_HPP

# include <list>
# include <iostream>
# include "Nibbler.hpp"
# include "IAudioLib.hpp"

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
		bool	moveSnake(eDir*, IAudioLib &);
		static GameCore &	getGame(short, short, short, bool);
		void	_printMap(void) const;
		Data &	getData(void);

	private:
		GameCore(short, short, short, bool);
		GameCore(void);

		bool	_movePlayer(eDir, snakeData &, eNum, IAudioLib & sound);
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
