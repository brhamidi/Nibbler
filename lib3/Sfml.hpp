/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sfml.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:58:59 by bhamidi           #+#    #+#             */
/*   Updated: 2018/06/11 14:45:15 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFML_HPP
# define SFML_HPP

# include "IGraphicLib.hpp"
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <iostream>
# include <map>

# define VALUE	25
# define MENU	3

class Sfml : public IGraphicLib
{
	public:
		Sfml(short, short);
		~Sfml(void);

		void	render(Data const &);
		void	getEvent(eDir *);

	private:
		void	_init(short, short);
		void	_stop(void);
		void	_handle_object(short, short, sf::Sprite *);

		std::map<int, eDir > 		 _dir;
		std::map<int, eDir > 		 _interaction;
		std::map<int, sf::Sprite * > _map;
		sf::RenderWindow			*_window;
		sf::Texture					_texture;
		sf::Font					_font;
		sf::Text					_text;
		sf::Text					_ntext;

		sf::Texture					_head;
		sf::Texture					_head2;
		sf::Sprite					_sHead;
		sf::Sprite					_sHead2;
		sf::Texture					_snake;
		sf::Sprite					_sSnake;
		sf::Texture					_snake2;
		sf::Sprite					_sSnake2;
		sf::Texture					_custom;
		sf::Sprite					_sCustom;
		sf::Texture					_food;
		sf::Sprite					_sFood;
		sf::Texture					_obstacle;
		sf::Sprite					_sObstacle;
		sf::Texture					_wall;
		sf::Sprite					_sWall;

};

extern "C"
{
	IGraphicLib	*createGraphicLib(short, short);
	void		deleteGraphicLib(IGraphicLib *);
}

#endif
