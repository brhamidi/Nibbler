/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl2.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:16:39 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/22 15:25:29 by msrun            ###   ########.fr       */
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

	this->_win = SDL_CreateWindow("Nibbler" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , x, y, 0);

//	SDL_Point ligne_depart,ligne_arrivee; // Déclaration du point de départ et du point d'arrivée d'une ligne


	if(SDL_VideoInit(NULL) < 0) // Initialisation de la SDL
	{
		std::cerr << "Erreur d'initialisation de la SDL : " << SDL_GetError() << std::endl;
		throw "Error";
	}

	// Création de la fenêtre :
	this->_win = SDL_CreateWindow("Une this->_win SDL" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 800 , 800 , 0);
	if(this->_win == NULL) // Gestion des erreurs
	{
		std::cerr << "Erreur lors de la creation d'une this->_win : " << SDL_GetError() << std::endl;
		throw "Error";
	}

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
    SDL_SetRenderDrawColor(this->_renderer,0,0,0,255);
    SDL_RenderClear(this->_renderer);
    // Le fond est à présent noir
    
	SDL_SetRenderDrawColor(this->_renderer,200 ,0 ,0 ,200); //Couleur blanche
    
	SDL_Rect cases[data._width * data._height]; // Déclaration du tableau contenant les cases blanches

	// Nous allons maintenant remplir les cases blanches par dessus le fond noir
	// Remplissage du tableau de SDL_Rect que l'on remplira ensuite avec du blanc :

	int icases = 0;
	for (auto h = 0; h < data._height; h++)
	{
		for (auto w = 0; w < data._width; w++)
		{
			cases[icases].x = cases[icases].y = data._width;
			cases[icases].w = cases[icases].h = data._height;
			++icases;
		}
	}

	if(SDL_RenderFillRects(this->_renderer,cases,32) <0)//Remplissage des cases blanches
	{
		std::cerr << "Erreur lors des remplissages de rectangles: " << SDL_GetError() << std::endl;
		throw "Error";
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
