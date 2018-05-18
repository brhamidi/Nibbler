/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:32:47 by msrun             #+#    #+#             */
/*   Updated: 2018/05/18 14:01:15 by msrun            ###   ########.fr       */
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

GameCore::GameCore(short width, short height) : _fed(false), _direction(3)
{
	if (width < 10)
		throw "width too small";
	else if (height < 10)
		throw "height too small";
	this->_data._score = 0;
	this->_data._width = width;
	this->_data._height = height;
	this->_snake = {
			{height / 2, width / 2}, {height / 2, width / 2 + 1},
			{height / 2, width / 2 + 2}, {height / 2, width / 2 + 3}
		};
	this->_data._map = new short * [this->_data._height];
	for (auto h = 0; h < this->_data._height; h++)
		this->_data._map[h] = new short[this->_data._width]();
	_buildTheWall();
	_popFood();
	for(auto corps: this->_snake)
		this->_updateSnake(corps, true);
	return ;
}

GameCore &	GameCore::getGame(short width, short height)
{
	static	GameCore g = GameCore(width, height);

	return g;
}

void	GameCore::_printMap(void) const
{
	for (auto h = 0; h < this->_data._height; h++)
	{
		std::cout << std::endl;
		for (auto w = 0; w < this->_data._width; w++)
		{
			if (_data._map[h][w] == eNum::Snake )
				std::cout << GREEN << "  " << RESET;
			if (_data._map[h][w] == eNum::Food )
				std::cout << YELLOW << "  " << RESET;
			if (_data._map[h][w] == eNum::Wall )
				std::cout << RED << "  " << RESET;
			if (_data._map[h][w] == eNum::Blank )
				std::cout << BLACK << "  " << RESET;
		}
	}
	std::cout << std::endl;
}

void	GameCore::_buildTheWall(void)
{
	for (int i = 0; i < this->_data._width; i++)
	{
		this->_data._map[0][i] = eNum::Wall;
		this->_data._map[this->_data._height - 1][i] = eNum::Wall;
	}
	for (int i = 0; i < this->_data._height; i++)
	{
		this->_data._map[i][0] = eNum::Wall;
		this->_data._map[i][this->_data._width - 1] = eNum::Wall;
	}
}

bool GameCore::moveSnake(int input)
{
	static const std::pair<char, char> getDirection[4] =
	{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

	if (input != -1)
	{
		if(input % 2 != this->_direction % 2)
			this->_direction = input;
	}

	bool tmp = false;
	std::pair <short, short> newHead =
	{this->_snake.begin()->first + getDirection[this->_direction].first,
	   	this->_snake.begin()->second + getDirection[this->_direction].second};

	if (newHead.second < this->_data._width && newHead.second >= 0 &&
		newHead.first < this->_data._height && newHead.first >= 0 &&
		(this->_data._map[newHead.first][newHead.second] == eNum::Wall ||
		this->_data._map[newHead.first][newHead.second] == eNum::Snake))
		return false;
	if (newHead.second < this->_data._width && newHead.second >= 0 &&
		newHead.first < this->_data._height && newHead.first >= 0 &&
		this->_data._map[newHead.first][newHead.second] == eNum::Food)
	{
		this->_popFood();
		tmp = true;
	}

	this->_snake.push_front(newHead);
	this->_updateSnake(*(this->_snake.begin()), true);

	if (this->_fed == false)
	{
		this->_updateSnake(*(std::next(this->_snake.end(), -1)), false);
		this->_snake.pop_back();
	}
	else
		this->_fed = false;
	if (tmp)
		this->_fed = true;
	return true;
}

void	GameCore::_updateSnake(std::pair<short, short> & _snakePos, bool update)
{
	if (_snakePos.second < this->_data._width && _snakePos.second >= 0 &&
		_snakePos.first < this->_data._height && _snakePos.first >= 0 )
	{
		this->_data._map[_snakePos.first][_snakePos.second] =
			(update ? eNum::Snake : eNum::Blank);
	}
}

bool GameCore::_findPos(short y, short x, short limitY, short limitX)
{
	for (; y < limitY; y++)
	{
		for ( ; x < limitX; x++)
			if (_data._map[y][x] == 0)
			{
				_data._map[y][x] = eNum::Food;
				return true;
			}
		x = 0;
	}
	return false;
}

void	GameCore::_popFood(void)
{
	short x = std::rand() % (this->_data._width - 2) + 1;
	short y = std::rand() % (this->_data._height - 2) + 1;

	if (_findPos(y, x, this->_data._height, this->_data._width) == false)
		if (_findPos(1, 1, this->_data._height, this->_data._width) == false)
			std::cout << "Winner !" << std::endl;
}
