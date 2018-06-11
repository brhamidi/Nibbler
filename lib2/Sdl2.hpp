/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl2.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:18:05 by bhamidi           #+#    #+#             */
/*   Updated: 2018/06/11 14:49:29 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL2_HPP
# define SDL2_HPP

# include "IGraphicLib.hpp"
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <map>

# define MENU	8

class Sdl2 : public IGraphicLib
{
	public:
		Sdl2(short, short);
		~Sdl2(void);

		void	render(Data const &);
		void	getEvent(eDir *);

	private:
		SDL_Window		*_win;
		SDL_Renderer	*_renderer;
		TTF_Font		*_font;
		SDL_Color		_font_color;
		SDL_Color		_color_black;
		SDL_Surface		*_text_surface;
		SDL_Texture		*_msg;
		SDL_Surface		*_ntext_surface;
		SDL_Texture		*_nmsg;

		SDL_Color	_renderColors[eNum::Snake2 + 1];
		std::map < int, eDir > _libMap;
		std::map < int, eDir > _snake1Map;
		std::map < int, eDir > _snake2Map;

		void	_init(short, short);
		void	_stop(void);
};

extern "C"
{
	IGraphicLib	*createGraphicLib(short, short);
	void		deleteGraphicLib(IGraphicLib *);
}

#endif
