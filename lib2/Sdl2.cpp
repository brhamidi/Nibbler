/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl2.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:16:39 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/22 15:19:56 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sdl2.hpp"

Sdl2::~Sdl2(void)
{
	this->_stop();
}

Sdl2::Sdl2(short x, short y)
{
	this->_init(x, y);
}

void	Sdl2::_stop(void)
{
	SDL_DestroyWindow(this->_win);
	SDL_Quit();
}

void	Sdl2::_init(short x, short y) 
{
	SDL_Init(SDL_INIT_VIDEO);

	this->_win = SDL_CreateWindow("Nibbler" , SDL_WINDOWPOS_CENTERED ,
			SDL_WINDOWPOS_CENTERED , x, y, SDL_WINDOW_SHOWN);
	SDL_Delay(10000);
}

void	Sdl2::render(Data const &) const
{
}

eDir	Sdl2::getEvent(void) const
{
	static eDir	direction = eDir::Left;
	eDir		tmp = direction;
	SDL_Event 	event;

	SDL_WaitEvent(&event); 
    switch (event.type)
    {
		case SDL_QUIT: direction = eDir::Exit; break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_LEFT:  direction = eDir::Left; break;
				case SDLK_RIGHT: direction = eDir::Right; break;
				case SDLK_UP:    direction = eDir::Up; break;
				case SDLK_DOWN:  direction = eDir::Down; break;
			}
			break;
    }
	if (direction % 2 == tmp % 2)
		direction = tmp;
	return direction;
}

IGraphicLib	*createGraphicLib(short x, short y)
{
	return new Sdl2(x, y);
}

void	deleteGraphicLib(IGraphicLib *graphicLib)
{
	delete graphicLib;
}
