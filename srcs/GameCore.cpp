/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:32:47 by msrun             #+#    #+#             */
/*   Updated: 2018/05/15 19:30:00 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"

GameCore::~GameCore(void)
{
	return ;
}

GameCore const &	GameCore::getGame(short width, short height)
{
	static	GameCore(width, height);

	return GameCore;
}

void	GameCore::_buildTheWall(void)
{
	for (int i = 0; i < this->_width, i++)
	{
		this->_map[0][i] = -1;
		this->_map[this->_height][i] = -1;
	}
}

GameCore::GameCore(short width, short height)
	: _score(0), _width(width), _height(height),
   	_snake({{width / 2, height / 2}, {width / 2 + 1, height / 2}, {width / 2 + 2, height / 2}, {width / 2 + 3, height / 2}})
{
	if (this->_width < 10)
		throw "width too small";
	else if (this_height < 10)
		throw "height too small";
	_buildTheWall();
	_popFood();
	return ;
}
