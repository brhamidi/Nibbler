/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:32:47 by msrun             #+#    #+#             */
/*   Updated: 2018/06/04 18:16:05 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"

GameCore::~GameCore(void)
{
//	for (auto h = 0; h < this->_data._height; h++)
//		delete [] this->_data._map[h];
//	delete [] this->_data._map;
	return ;
}

GameCore::GameCore(short width, short height, short obstacle, bool p2)
	: _p2(p2)
{
	if (width < 10)
		throw "width too small";
	else if (height < 10)
		throw "height too small";

	this->_data._width = width;
	this->_data._height = height;

	this->_data._map = new short * [this->_data._height];
	for (auto h = 0; h < this->_data._height; h++)
		this->_data._map[h] = new short[this->_data._width]();

	this->_data._score = 0;

	{
		this->_snake.snake =
		{{height / (p2 ? 3 : 2), width / 2}, {height / (p2 ? 3 : 2), width / 2 + 1},
			{height / (p2 ? 3 : 2), width / 2 + 2}, {height / (p2 ? 3 : 2), width / 2 + 3}};
		this->_initSnake(this->_snake);
	}

	if(p2)
	{
		this->_snake2.snake =
		{{height * 2 / 3, width / 2}, {height * 2 / 3, width / 2 + 1},
			{height * 2 / 3, width / 2 + 2}, {height * 2 / 3, width / 2 + 3}};
		this->_initSnake(this->_snake2);
	}
	_buildTheWall();

	for(auto corps : this->_snake.snake)
		this->_updateSnake(corps, eNum::Snake);
	this->_updateSnake(*this->_snake.snake.begin(), eNum::Head);
	if (p2)
	{
		for(auto corps : this->_snake2.snake)
			this->_updateSnake(corps, eNum::Snake);
		this->_updateSnake(*this->_snake2.snake.begin(), eNum::Head);
	}
	_popElem(eNum::Food);
	for (int i = 0; i < obstacle; i++)
		_popElem(eNum::Obstacle);
	return;
}

void	GameCore::_initSnake(snakeData snake)
{
	snake.fed = false;
	snake.direction = eDir::Left;
}

GameCore &	GameCore::getGame(short width, short height, short o, bool player)
{
	static	GameCore g = GameCore(width, height, o, player);

	return g;
}

Data &	GameCore::getData(void)
{
	return this->_data;
}

void	GameCore::_printMap(void) const
{
	for (auto h = 0; h < this->_data._height; h++)
	{
		std::cout << std::endl;
		for (auto w = 0; w < this->_data._width; w++)
		{
			if (_data._map[h][w] == eNum::Head )
				std::cout << CYAN << "  " << RESET;
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

bool GameCore::moveSnake(eDir *input)
{
	this->_data._snakeDir = this->_snake.direction;
	this->_data._snakeDir2 = this->_snake2.direction;
	if (!this->_movePlayer(input[0], this->_snake))
		return false;
	else if (this->_p2)
		return this->_movePlayer(input[1], this->_snake2);
	return true;
}

bool	GameCore::_movePlayer(eDir input, snakeData & snake)
{
	static const std::pair<char, char> getDirection[4] =
	{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

	if (input > eDir::Left)
		input = snake.direction;
	if (input != eDir::Error)
	{
		if(input % 2 != snake.direction % 2) //check if direction is not opposite
			snake.direction = input;
	}

	bool onFood = false;

	std::pair <short, short> newHead =
	{
		snake.snake.begin()->first + getDirection[snake.direction].first,
	   	snake.snake.begin()->second + getDirection[snake.direction].second
	};

	if (newHead.second < this->_data._width && newHead.second >= 0 &&
		newHead.first < this->_data._height && newHead.first >= 0)
	{
		if ( this->_data._map[newHead.first][newHead.second] != eNum::Blank
				&& this->_data._map[newHead.first][newHead.second] != eNum::Food
			   	&& (newHead.first != (std::next(this->_snake2.snake.end(), -1))->first
				|| newHead.second != (std::next(this->_snake2.snake.end(), -1))->second)
				&& (newHead.first != (std::next(snake.snake.end(), -1))->first
				|| newHead.second != (std::next(snake.snake.end(), -1))->second))
				return false;
		if ( this->_data._map[newHead.first][newHead.second] == eNum::Food )
		{
			this->_popElem(eNum::Food);
			onFood = true;
			_data._score += 1000;
		}
	}

	if (snake.fed == false)
	{
		if (!(std::next(snake.snake.end(), -1)->first == this->_snake.snake.begin()->first
				&& std::next(snake.snake.end(), -1)->second == this->_snake.snake.begin()->second))
			this->_updateSnake(*(std::next(snake.snake.end(), -1)), eNum::Blank);
		snake.snake.pop_back();
	}
	else
		snake.fed = false;

	snake.snake.push_front(newHead);
	this->_updateSnake( * (snake.snake.begin()), eNum::Head );
	this->_updateSnake( * std::next(snake.snake.begin()) , eNum::Snake );

	if (onFood)
		snake.fed = true;
	return true;
}

void	GameCore::_updateSnake(std::pair<short, short> & _snakePos, eNum form)
{
	if (_snakePos.second < this->_data._width && _snakePos.second >= 0 &&
		_snakePos.first < this->_data._height && _snakePos.first >= 0 )
		this->_data._map[_snakePos.first][_snakePos.second] = form;
}

bool	GameCore::_findPos(short y, short x, short limitY, short limitX, eNum e)
{
	for (; y < limitY; y++)
	{
		for ( ; x < limitX; x++)
			if (_data._map[y][x] == 0)
			{
				_data._map[y][x] = e;
				return true;
			}
		x = 0;
	}
	return false;
}

void	GameCore::_popElem(eNum e)
{
	short x = std::rand() % (this->_data._width - 2) + 1;
	short y = std::rand() % (this->_data._height - 2) + 1;

	if (_findPos(y, x, this->_data._height, this->_data._width, e) == false)
		if (_findPos(1, 1, this->_data._height, this->_data._width, e) == false)
			std::cout << "Winner !" << std::endl;
}
