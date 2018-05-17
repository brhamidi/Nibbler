/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:32:47 by msrun             #+#    #+#             */
/*   Updated: 2018/05/17 12:50:45 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"
#include <iostream>

GameCore::~GameCore(void)
{
	for (auto h = 0; h < this->_data._height; h++)
		delete [] this->_data._map[h];
	delete [] this->_data._map;
	return ;
}

GameCore::GameCore(short width, short height)
{
	if (width < 10)
		throw "width too small";
	else if (height < 10)
		throw "height too small";
	this->_data._score = 0;
	this->_data._width = width;
	this->_data._height = height;
	this->_snake = {
			{width / 2, height / 2}, {width / 2 + 1, height / 2},
			{width / 2 + 2, height / 2}, {width / 2 + 3, height / 2}
		};
	this->_data._map = new short * [this->_data._height];
	for (auto h = 0; h < this->_data._height; h++)
		this->_data._map[h] = new short[this->_data._width]();
	_buildTheWall();
	_popFood();
	this->_data._map[this->_data._height / 2][this->_data._width / 2] = 2;
	this->_data._map[this->_data._height / 2][this->_data._width / 2 + 1] = 2;
	this->_data._map[this->_data._height / 2][this->_data._width / 2 + 2] = 2;
	this->_data._map[this->_data._height / 2][ this->_data._width / 2 + 3] = 2;

	//_printMap();
	return ;
}

GameCore &	GameCore::getGame(short width, short height)
{
	static	GameCore g = GameCore(width, height);

	return g;
}

void	GameCore::_printMap(void)
{
	for (auto h = 0; h < this->_data._height; h++)
	{
		std::cout << std::endl;
		for (auto w = 0; w < this->_data._width; w++)
			std::cout << this->_data._map[h][w];
	}
	std::cout << std::endl;
}

void	GameCore::_buildTheWall(void)
{
	for (int i = 0; i < this->_data._width; i++)
	{
		this->_data._map[0][i] = 1;
		this->_data._map[this->_data._height - 1][i] = 1;
	}
	for (int i = 0; i < this->_data._height; i++)
	{
		this->_data._map[i][0] = 1;
		this->_data._map[i][this->_data._width - 1] = 1;
	}
}

void	GameCore::moveSnake(int input)
{
	std::cout << input << std::endl;
	switch(input)
	{
		case KEY_UP:
			mvup();
			break;
		case KEY_DOWN:
			mvdown();
			break;
		case KEY_LEFT:
			mvleft();
			break;
		case KEY_RIGHT:
			mvright();
			break;
		case 32:
			this->attack(list);
		default:
			break;
	}
}

void	GameCore::_popFood(void)
{
	std::srand(std::time(nullptr));
	while (1)
	{
		short x = std::rand() % this->_data._width + 1;
		short y = std::rand() % this->_data._height + 1;

		if (this->_data._map[y][x] == 0)
		{
			this->_data._map[y][x] = 3;
			return ;
		}
	}
}
