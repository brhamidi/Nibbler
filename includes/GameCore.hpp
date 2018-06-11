/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:21:35 by msrun             #+#    #+#             */
/*   Updated: 2018/06/11 17:10:35 by bhamidi          ###   ########.fr       */
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
		void	handle_custom(unsigned short *custom);
		Data &	getData(void);

	private:
		GameCore(short, short, short, bool);
		GameCore(void);
		GameCore & operator=(GameCore const &);
		GameCore(GameCore const &);

		bool	_movePlayer(eDir, snakeData &, eNum, eNum, IAudioLib & sound);
		void	_initSnake(snakeData);
		bool	_findPos(short, short, short, short, eNum, eNum);
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
