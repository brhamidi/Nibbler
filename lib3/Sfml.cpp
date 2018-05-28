/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sfml.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:00:10 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/28 12:28:01 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sfml.hpp"

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
	this->_window = new sf::RenderWindow(sf::VideoMode( x * VALUE, (y + MENU) * VALUE), "Nibbler");
	this->_texture.loadFromFile("lib3/img1.png", sf::IntRect(0, 0, x * VALUE + 13, MENU * VALUE));
	this->_texture.setSmooth(true);
	this->_sprite.setTexture(this->_texture);
}

void	Sfml::getEvent(eDir *direction) const
{
	eDir		tmp[2];
	sf::Event 	event;

	tmp[0] = direction[0];
	tmp[1] = direction[1];
	while ( this->_window->pollEvent(event) )
	{
		if (tmp[0] != direction[0] && tmp[1] != direction[1])
			break ;
		if (!direction[2])
 		   	switch (event.type)
	   	 	{
				case sf::Event::Closed: direction[2] = eDir::Exit; break;
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::Delete:  direction[2] = eDir::Exit; break;
						case sf::Keyboard::Num1:  direction[2] = eDir::Lib1; break;
						case sf::Keyboard::Num2:  direction[2] = eDir::Lib2; break;
						case sf::Keyboard::Num3:  direction[2] = eDir::Lib3; break;
						default: break;
					}
					break;
				default: break;
   		 	}
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
			rectangle.setPosition(w * VALUE, (h + MENU) * VALUE);
			this->_window->draw(rectangle);
		}
	}
	this->_window->draw(this->_sprite);

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
