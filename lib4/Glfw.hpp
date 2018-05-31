/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glfw.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:12:15 by msrun             #+#    #+#             */
/*   Updated: 2018/05/31 19:33:13 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFML_HPP
# define SFML_HPP

# include "IGraphicLib.hpp"
# include <GLFW/glfw3.h>
# include "linmath.h"
# include <map>

# define VALUE	15
# define MENU	20

struct vertexMap
{
	float x, y;
	float r, g, b;
};

class Glfw : public IGraphicLib
{
	public:
		Glfw(short, short);
		~Glfw(void);

		void	render(Data const &);
		void	getEvent(eDir *);
		eDir *	getKeycallback(void);
		std::map <int, eDir > & getDirectionMap(void);
		std::map <int, eDir > & getDirection2Map(void);
		std::map <int, eDir > & getInteractionMap(void);

	private:
		void	_init(short, short);
		void	_stop(void);
		void	_setVerticesDraw(int pos, vertexMap , Data const &);
		void	_setVertice(int pos, vertexMap , Data const &);

		GLFWwindow	*_window;
		GLuint		*_program;
		GLint		*_mvp_location;
		vertexMap	*_vertices;
		eDir		_keycallback[4];
		std::map < int, eDir > _directionMap;
		std::map < int, eDir > _direction2Map;
		std::map < int, eDir > _interactionMap;
};

extern "C"
{
	IGraphicLib	*createGraphicLib(short, short);
	void		deleteGraphicLib(IGraphicLib *);
}

#endif
