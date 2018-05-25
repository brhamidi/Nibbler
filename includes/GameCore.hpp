/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:21:35 by msrun             #+#    #+#             */
/*   Updated: 2018/05/25 16:06:35 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMECORE_HPP
# define GAMECORE_HPP

#include <list>
#include <iostream>
#include "Nibbler.hpp"

class GameCore
{
	public:
		~GameCore(void);
		static GameCore &	getGame(short, short, short);
		bool	moveSnake(eDir);
		void	_printMap(void) const;
		Data &	getData(void);

	private:
		GameCore(short, short, short);
		GameCore(void);
		bool	_findPos(short, short, short, short, eNum);
		void	_buildTheWall(void);
		void	_popElem(eNum);
		void	_updateSnake(std::pair<short, short> &, eNum);

		std::list< std::pair< short, short > >	_snake;
		bool	_fed;
		eDir	_direction;
		Data	_data;
};

#endif
