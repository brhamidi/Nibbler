/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sfml.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:00:10 by bhamidi           #+#    #+#             */
/*   Updated: 2018/06/11 16:35:22 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sfml.hpp"

Sfml::~Sfml(void)
{
	this->_stop();
}

Sfml::Sfml(short x, short y)
{
	this->_init(x, y);
}

void	Sfml::_stop(void)
{
	this->_window->close();
	delete this->_window;
}

void	Sfml::_init(short x, short y) 
{
	this->_window = new sf::RenderWindow(sf::VideoMode( x * VALUE, (y + MENU) * VALUE), "Nibbler");

	this->_font.loadFromFile("lib3/font.ttf");

	this->_text.setFont(this->_font);
	this->_text.setString("Score: ");
	this->_text.setCharacterSize(40);
	this->_text.setFillColor(sf::Color::White);

	this->_ntext.setFont(this->_font);
	this->_ntext.setCharacterSize(40);
	this->_ntext.setFillColor(sf::Color::White);
	this->_ntext.setPosition(sf::Vector2f(100, 0));

	this->_snake.loadFromFile("lib3/snake.png");
	this->_sSnake.setTexture(_snake);
	this->_sSnake.setScale(sf::Vector2f(0.05, 0.05));

	this->_snake2.loadFromFile("lib3/snake2.png");
	this->_sSnake2.setTexture(_snake2);
	this->_sSnake2.setScale(sf::Vector2f(0.35, 0.35));

	this->_head.loadFromFile("lib3/head.png");
	this->_sHead.setTexture(_head);
	this->_sHead.setScale(sf::Vector2f(0.15, 0.15));

	this->_head2.loadFromFile("lib3/head2.png");
	this->_sHead2.setTexture(_head2);
	this->_sHead2.setScale(sf::Vector2f(0.15, 0.15));

	this->_food.loadFromFile("lib3/food.png");
	this->_sFood.setTexture(_food);
	this->_sFood.setScale(sf::Vector2f(0.07, 0.07));

	this->_custom.loadFromFile("lib3/custom.png");
	this->_sCustom.setTexture(_custom);
	this->_sCustom.setScale(sf::Vector2f(0.3, 0.3));

	this->_wall.loadFromFile("lib3/fence.png");
	this->_sWall.setTexture(_wall);
	this->_sWall.setScale(sf::Vector2f(0.15, 0.15));


	this->_obstacle.loadFromFile("lib3/obstacle.png");
	this->_sObstacle.setTexture(_obstacle);
	this->_sObstacle.setScale(sf::Vector2f(0.15, 0.15));

	_map[eNum::Wall] = & this->_sWall;
	_map[eNum::Obstacle] = & this->_sObstacle;
	_map[eNum::Food] = & this->_sFood;
	_map[eNum::Snake] = & this->_sSnake;
	_map[eNum::Head] = & this->_sHead;
	_map[eNum::Head2] = & this->_sHead2;
	_map[eNum::Custom] = & this->_sCustom;
	_map[eNum::Snake2] = & this->_sSnake2;

	this->_dir[sf::Keyboard::Left] = eDir::Left;
	this->_dir[sf::Keyboard::Right] = eDir::Right;
	this->_dir[sf::Keyboard::Up] = eDir::Up;
	this->_dir[sf::Keyboard::Down] = eDir::Down;

	this->_dir2[sf::Keyboard::A] = eDir::Left;
	this->_dir2[sf::Keyboard::D] = eDir::Right;
	this->_dir2[sf::Keyboard::W] = eDir::Up;
	this->_dir2[sf::Keyboard::S] = eDir::Down;

	this->_interaction[sf::Keyboard::Num1] = eDir::Lib1;
	this->_interaction[sf::Keyboard::Num2] = eDir::Lib2;
	this->_interaction[sf::Keyboard::Num3] = eDir::Lib3;
	this->_interaction[sf::Keyboard::Delete] = eDir::Exit;
}

void	Sfml::render(Data const & data)
{
	this->_window->clear(sf::Color::Black);

	_ntext.setString(std::to_string(data._score));
	for (auto h = 0; h < data._height; h++)
		for (auto w = 0; w < data._width; w++)
			if (data._map[h][w] != eNum::Blank)
				_handle_object(w, h, _map[ data._map[h][w] ]);

	this->_window->draw(_ntext);
	this->_window->draw(_text);

	this->_window->display();
}

void		Sfml::_handle_object(short w, short h, sf::Sprite * sprite)
{
	sprite->setPosition(w * VALUE - VALUE / 2, (h + MENU) * VALUE - VALUE / 2);
	this->_window->draw(*sprite);
}


void	Sfml::_checkEvent(eDir tmp, eDir & direction,  sf::Event event, std::map < int, eDir> & map) const
{
	if (tmp == direction && event.type == sf::Event::KeyPressed && map.find(event.key.code) != map.end())
	{
		direction = map[event.key.code];
		if (direction % 2 == tmp % 2)
			direction = tmp;
	}
}

void	Sfml::getEvent(eDir *direction)
{
	eDir		tmp[2];
	sf::Event 	event;

	tmp[0] = direction[0];
	tmp[1] = direction[1];

	while ((tmp[0] == direction[0] || tmp[1] == direction[1]) && this->_window->pollEvent(event) )
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			if (direction[3] == eDir::Space)
				direction[3] = eDir::Up;
			else
				direction[3] = eDir::Space;
		}

		if (!direction[2] && event.type == sf::Event::KeyPressed)
			direction[2] = this->_interaction[event.key.code];

		if (direction[3] != eDir::Space)
		{
			this->_checkEvent(tmp[0], direction[0], event, this->_dir);
			this->_checkEvent(tmp[1], direction[1], event, this->_dir2);
		}
	}
}

IGraphicLib	*createGraphicLib(short x, short y)
{
	return new Sfml(x, y);
}

void	deleteGraphicLib(IGraphicLib *graphicLib)
{
	delete graphicLib;
}
