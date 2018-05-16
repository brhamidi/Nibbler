/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:32:47 by msrun             #+#    #+#             */
/*   Updated: 2018/05/16 17:12:27 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"
#include <iostream>

GameCore::~GameCore(void)
{
	for (auto h = 0; h < this->_height; h++)
		delete [] this->_map[h];
	delete [] this->_map;
	return ;
}

GameCore::GameCore(short width, short height)
	: _score(0), _width(width), _height(height),
		_snake({{width / 2, height / 2}, {width / 2 + 1, height / 2},
				{width / 2 + 2, height / 2}, {width / 2 + 3, height / 2}})
{
	if (this->_width < 10)
		throw "width too small";
	else if (this->_height < 10)
		throw "height too small";
	this->_map = new short * [this->_height];
	_buildTheWall();
	_printMap();
	return ;
}

GameCore const &	GameCore::getGame(short width, short height)
{
	static	GameCore g = GameCore(width, height);

	return g;
}

void	GameCore::_printMap(void)
{
	for (auto h = 0; h < this->_height; h++)
	{
		std::cout << std::endl;
		for (auto w = 0; w < this->_width; w++)
			std::cout << this->_map[h][w];
	}
	std::cout << std::endl;
}

void	GameCore::_buildTheWall(void)
{
	for (auto h = 0; h < this->_height; h++)
		this->_map[h] = new short[this->_width]();
	for (int i = 0; i < this->_width; i++)
	{
		this->_map[0][i] = 1;
		this->_map[this->_height - 1][i] = 1;
	}
	for (int i = 0; i < this->_height; i++)
	{
		this->_map[i][0] = 1;
		this->_map[i][this->_width - 1] = 1;
	}
}
