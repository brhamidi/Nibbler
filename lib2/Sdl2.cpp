/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl2.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:16:39 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/22 17:00:33 by msrun            ###   ########.fr       */
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

	this->_win = SDL_CreateWindow("Nibbler" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , x * 10 , y * 10, 0);

//	SDL_Point ligne_depart,ligne_arrivee; // Déclaration du point de départ et du point d'arrivée d'une ligne

	// Création du this->_renderer :
	this->_renderer = SDL_CreateRenderer(this->_win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du this->_renderer
	if(this->_renderer == NULL) // Gestion des erreurs
	{
		std::cerr << "Erreur lors de la creation d'un this->_renderer : " << SDL_GetError() << std::endl;
		throw "Error";
	}
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
			cases.x = w * 10;
			cases.y = h * 10;
			if(SDL_RenderFillRect(this->_renderer, &cases) < 0)
			{
				std::cerr << "Erreur lors des remplissages de rectangles: " << SDL_GetError() << std::endl;
				throw "Error";
			}
		}
	}
	SDL_RenderPresent(this->_renderer);
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
