/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl2.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:18:05 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/24 15:33:18 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL2_HPP
# define SDL2_HPP

# include "IGraphicLib.hpp"
# include <SDL2/SDL.h>

class Sdl2 : public IGraphicLib
{
	public:
		Sdl2(short, short);
		~Sdl2(void);

		void	render(Data const &) const;
		eDir	getEvent(void) const;

	private:
		SDL_Window		*_win;
		SDL_Renderer	*_renderer;

		void	_init(short, short);
		void	_stop(void);

};

extern "C"
{
	IGraphicLib	*createGraphicLib(short, short);
	void		deleteGraphicLib(IGraphicLib *);
}

#endif
