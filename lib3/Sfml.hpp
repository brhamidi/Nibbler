/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sfml.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:58:59 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/25 18:25:52 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFML_HPP
# define SFML_HPP

# include "IGraphicLib.hpp"
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>

# define VALUE	15
# define MENU	20

class Sfml : public IGraphicLib
{
	public:
		Sfml(short, short);
		~Sfml(void);

		void	render(Data const &) const;
		eDir	getEvent(void) const;

	private:
		void	_init(short, short);
		void	_stop(void);

		sf::RenderWindow	*_window;
		sf::Sprite			_sprite;
		sf::Texture			_texture;

};

extern "C"
{
	IGraphicLib	*createGraphicLib(short, short);
	void		deleteGraphicLib(IGraphicLib *);
}

#endif
