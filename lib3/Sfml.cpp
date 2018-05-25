/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sfml.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:00:10 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/25 17:00:06 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sfml.hpp"
#include <iostream>

Sfml::~Sfml(void)
{
	this->_stop();
}

Sfml::Sfml(short x, short y)
	: _window()
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
	this->_window = new sf::RenderWindow(sf::VideoMode(x * VALUE, y * VALUE), "Nibbler");
}

eDir *	Sfml::getEvent(void) const
{
	static eDir	direction[2] = {eDir::Left, eDir::Left};
	eDir		tmp[2];
	sf::Event 	event;

	tmp[0] = direction[0];
	tmp[1] = direction[1];
	while ( this->_window->pollEvent(event) )
	{
		if (tmp[0] != direction[0] && tmp[1] != direction[1])
			break;
		if (tmp[0] == direction[0])
		{
			tmp[0] = direction[0];

			switch (event.type)
			{
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::Left:  direction[0] = eDir::Left; break;
						case sf::Keyboard::Right: direction[0] = eDir::Right; break;
						case sf::Keyboard::Up:    direction[0] = eDir::Up; break;
						case sf::Keyboard::Down:  direction[0] = eDir::Down; break;
						default: break;
					}
					break;
				default: break;
			}
			if (direction[0] % 2 == tmp[0] % 2)
				direction[0] = tmp[0];
		}
		if (tmp[0] == direction[0])
		{
			tmp[0] = direction[0];

			switch (event.type)
			{
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::A:  direction[1] = eDir::Left; break;
						case sf::Keyboard::D: direction[1] = eDir::Right; break;
						case sf::Keyboard::W:    direction[1] = eDir::Up; break;
						case sf::Keyboard::S:  direction[1] = eDir::Down; break;
						default: break;
					}
					break;
				default: break;
			}
			if (direction[1] % 2 == tmp[1] % 2)
				direction[1] = tmp[1];
		}
	}
	while ( this->_window->pollEvent(event) ) ;
	return direction;
}

void	Sfml::render(Data const & data) const
{
	this->_window->clear(sf::Color::Black);

	sf::RectangleShape rectangle;

	for (auto h = 0; h < data._height; h++)
	{
		for (auto w = 0; w < data._width; w++)
		{
			if (data._map[h][w] == eNum::Obstacle)
				rectangle.setFillColor(sf::Color(1, 40, 78));
			if (data._map[h][w] == eNum::Blank)
				rectangle.setFillColor(sf::Color(255, 255, 0));
			if (data._map[h][w] == eNum::Wall)
				rectangle.setFillColor(sf::Color(255, 0, 255));
			if (data._map[h][w] == eNum::Snake)
				rectangle.setFillColor(sf::Color(0, 0, 255));
			if (data._map[h][w] == eNum::Head)
				rectangle.setFillColor(sf::Color(253, 109, 177));
			if (data._map[h][w] == eNum::Food)
				rectangle.setFillColor(sf::Color(1, 252, 235));
			rectangle.setSize(sf::Vector2f(VALUE, VALUE));
			rectangle.setPosition(w * VALUE, h * VALUE);
			this->_window->draw(rectangle);
		}
	}

	this->_window->display();
}

IGraphicLib	*createGraphicLib(short x, short y)
{
	return new Sfml(x, y);
}

void	deleteGraphicLib(IGraphicLib *graphicLib)
{
	delete graphicLib;
}
