/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl2.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:16:39 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/31 17:38:33 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sdl2.hpp"
#include <iostream>

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

	this->_win = SDL_CreateWindow("Une this->_win SDL" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED ,  x * 15, y * 15, 0);
	this->_renderer = SDL_CreateRenderer(this->_win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void	Sdl2::render(Data const & data) const
{
	SDL_Rect cases;
	for (auto h = 0; h < data._height; h++)
	{
		for (auto w = 0; w < data._width; w++)
		{
			if (data._map[h][w] == eNum::Blank)
				SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 200);
			if (data._map[h][w] == eNum::Wall)
				SDL_SetRenderDrawColor(this->_renderer, 255, 255, 0, 200);
			if (data._map[h][w] == eNum::Snake)
				SDL_SetRenderDrawColor(this->_renderer, 0, 255, 0, 200);
			if (data._map[h][w] == eNum::Head)
				SDL_SetRenderDrawColor(this->_renderer, 0, 255, 0, 200);
			if (data._map[h][w] == eNum::Food)
				SDL_SetRenderDrawColor(this->_renderer, 0, 0, 255, 200);
			if (data._map[h][w] == eNum::Obstacle)
				SDL_SetRenderDrawColor(this->_renderer, 0, 0, 255, 200);
			cases.x = w * 15;
			cases.y = h * 15;
			cases.w = cases.h = 15;
			if(SDL_RenderFillRect(this->_renderer, &cases) < 0)
			{
				std::cerr << "Erreur lors des remplissages de rectangles: " << SDL_GetError() << std::endl;
				throw "Error";
			}
		}
	}
	SDL_RenderPresent(this->_renderer);
}

void	Sdl2::getEvent(eDir *direction) const
{
	eDir		tmp[2];
	SDL_Event 	event;

	tmp[0] = direction[0];
	tmp[1] = direction[1];
	while ( SDL_PollEvent(&event) == 1 )
	{
		if (!direction[2])
			switch (event.key.keysym.sym)
			{
				case SDLK_DELETE:  direction[2] = eDir::Exit; break;
				case SDLK_1:  direction[2] = eDir::Lib1; break;
				case SDLK_2:  direction[2] = eDir::Lib2; break;
				case SDLK_3:  direction[2] = eDir::Lib3; break;
				default: break;
			}
		if (tmp[0] != direction[0] && tmp[1] != direction[1])
			break;
		if (tmp[0] == direction[0])
		{
			tmp[0] = direction[0];
			switch (event.type)
			{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_LEFT:  direction[0] = eDir::Left; break;
						case SDLK_RIGHT: direction[0] = eDir::Right; break;
						case SDLK_UP:    direction[0] = eDir::Up; break;
						case SDLK_DOWN:  direction[0] = eDir::Down; break;
					}
					break;
			}
			if (direction[0] % 2 == tmp[0] % 2)
				direction[0] = tmp[0];
		}
		if (tmp[0] == direction[0])
		{
			tmp[0] = direction[0];
			switch (event.type)
			{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_a:	direction[1] = eDir::Left; break;
						case SDLK_d:	direction[1] = eDir::Right; break;
						case SDLK_w:	direction[1] = eDir::Up; break;
						case SDLK_s:	direction[1] = eDir::Down; break;
					}
					break;
			}
			if (direction[1] % 2 == tmp[1] % 2)
				direction[1] = tmp[1];
		}
	}
}

IGraphicLib	*createGraphicLib(short x, short y)
{
	return new Sdl2(x, y);
}

void	deleteGraphicLib(IGraphicLib *graphicLib)
{
	delete graphicLib;
}
