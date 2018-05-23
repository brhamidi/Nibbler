/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sfml.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:00:10 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/23 15:10:01 by bhamidi          ###   ########.fr       */
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
	this->_window = new sf::Window(sf::VideoMode(600, 800), "Nibbler");
	this->_window->setSize(sf::Vector2u(x * 10, y * 10));
}

eDir	Sfml::getEvent(void) const
{
	static eDir	direction = eDir::Left;
	eDir		tmp = direction;
	sf::Event	event;

	while ( this->_window->pollEvent(event) )
	{
    	switch (event.type)
    	{
			case sf::Event::Closed: direction = eDir::Exit; break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Left:  direction = eDir::Left; break;
					case sf::Keyboard::Right: direction = eDir::Right; break;
					case sf::Keyboard::Up:    direction = eDir::Up; break;
					case sf::Keyboard::Down:  direction = eDir::Down; break;
					default: break;
				}
				break;
			default: break;
    	}
		if (direction % 2 == tmp % 2)
			direction = tmp;
		if (tmp != direction)
			break;
	}
	return direction;
}

void	Sfml::render(Data const &) const
{
}

IGraphicLib	*createGraphicLib(short x, short y)
{
	return new Sfml(x, y);
}

void	deleteGraphicLib(IGraphicLib *graphicLib)
{
	delete graphicLib;
}
