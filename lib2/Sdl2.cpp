/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl2.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:16:39 by bhamidi           #+#    #+#             */
/*   Updated: 2018/06/11 15:59:13 by msrun            ###   ########.fr       */
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

	TTF_Quit();
	SDL_Quit();
}

void	Sdl2::_init(short x, short y) 
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	this->_win = SDL_CreateWindow("Nibbler @ 42" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED ,  x * 15, (y + MENU) * 15, 0);
	this->_renderer = SDL_CreateRenderer(this->_win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// text
	this->_font = TTF_OpenFont("lib2/font.ttf", 15);
	this->_font_color = {121, 255, 77, 200};
	this->_color_black = {0, 0, 0, 200};
	this->_renderColors[eNum::Blank] = {0, 0, 0, 200};
	this->_renderColors[eNum::Wall] = {255, 255, 0, 200};
	this->_renderColors[eNum::Snake] = {0, 255, 0, 200};
	this->_renderColors[eNum::Head] = {255, 0, 0, 200};
	this->_renderColors[eNum::Head2] = {255, 255, 0, 200};
	this->_renderColors[eNum::Snake2] = {255, 129, 0, 200};
	this->_renderColors[eNum::Food] = {255, 163, 26, 200};
	this->_renderColors[eNum::Obstacle] = {255, 255, 255, 200};
	this->_renderColors[eNum::Custom] = {179, 67, 221, 200};

	this->_libMap[SDLK_DELETE] = eDir::Exit;
	this->_libMap[SDLK_1] = eDir::Lib1;
	this->_libMap[SDLK_2] = eDir::Lib2;
	this->_libMap[SDLK_3] = eDir::Lib3;
	this->_snake1Map[SDLK_LEFT] = eDir::Left;
	this->_snake1Map[SDLK_RIGHT] = eDir::Right;
	this->_snake1Map[SDLK_UP] = eDir::Up;
	this->_snake1Map[SDLK_DOWN] = eDir::Down;
	this->_snake2Map[SDLK_a] = eDir::Left;
	this->_snake2Map[SDLK_d] = eDir::Right;
	this->_snake2Map[SDLK_w] = eDir::Up;
	this->_snake2Map[SDLK_s] = eDir::Down;
}

void	Sdl2::render(Data const & data)
{
	SDL_Rect cases;

	SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->_renderer);

	this->_text_surface = TTF_RenderText_Shaded(this->_font, "Score:", this->_font_color, this->_color_black);
	this->_msg = SDL_CreateTextureFromSurface(this->_renderer, this->_text_surface);
	SDL_Rect Message_rect;
	Message_rect.x = 0;
	Message_rect.y = 0;
	Message_rect.w = 200;
	Message_rect.h = 60;

	this->_ntext_surface = TTF_RenderText_Shaded(this->_font, std::to_string(data._score).c_str(), this->_font_color, this->_color_black);
	this->_nmsg = SDL_CreateTextureFromSurface(this->_renderer, this->_ntext_surface);
	SDL_Rect nMessage_rect;
	nMessage_rect.x = 0;
	nMessage_rect.y = 50;
	nMessage_rect.w = 200;
	nMessage_rect.h = 60;

	SDL_RenderCopy(this->_renderer, this->_msg, NULL, & Message_rect);
	SDL_RenderCopy(this->_renderer, this->_nmsg, NULL, & nMessage_rect);

	for (auto h = 0; h < data._height; h++)
	{
		for (auto w = 0; w < data._width; w++)
		{
			SDL_SetRenderDrawColor(this->_renderer, this->_renderColors[data._map[h][w]].r, this->_renderColors[data._map[h][w]].g, this->_renderColors[data._map[h][w]].b, this->_renderColors[data._map[h][w]].a);
			cases.x = w * 15;
			cases.y = (h + MENU) * 15;
			cases.w = 15;
			cases.h = 15;
	
			SDL_RenderFillRect(this->_renderer, &cases);
		}
	}
	SDL_RenderPresent(this->_renderer);
	SDL_DestroyTexture(this->_msg);;
	SDL_DestroyTexture(this->_nmsg);;
	SDL_FreeSurface(this->_text_surface);
	SDL_FreeSurface(this->_ntext_surface);
}

void	Sdl2::_checkEvent(eDir tmp, eDir & direction,  SDL_Event event, std::map < int, eDir> & map) const
{
	if (tmp == direction && event.type == SDL_KEYDOWN && (map[event.key.keysym.sym] || event.key.keysym.sym == SDLK_UP))
	{
		direction = map[event.key.keysym.sym];
		if (direction % 2 == tmp % 2)
			direction = tmp;
	}
}

void	Sdl2::getEvent(eDir *direction)
{
	eDir		tmp[2];
	SDL_Event 	event;

	tmp[0] = direction[0];
	tmp[1] = direction[1];
	while ((tmp[0] == direction[0] || tmp[1] == direction[1]) && SDL_PollEvent(&event) == 1 )
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		{
			if (direction[3] == eDir::Space)
				direction[3] = eDir::Up;
			else
				direction[3] = eDir::Space;
		}

		if (!direction[2] && this->_libMap[event.key.keysym.sym])
			direction[2] = this->_libMap[event.key.keysym.sym];

		this->_checkEvent(tmp[0], direction[0], event, this->_snake1Map);
		this->_checkEvent(tmp[1], direction[1], event, this->_snake2Map);
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
