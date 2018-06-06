/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glfw.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:12:15 by msrun             #+#    #+#             */
/*   Updated: 2018/06/06 17:09:43 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFML_HPP
# define SFML_HPP

# include "IGraphicLib.hpp"
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "linmath.h"
# include <map>
# include <list>

# define VALUE	15
# define MENU	20

struct vertexMap
{
	float x, y;
	float r, g, b;
};

struct dataInfo
{
	int h, w, x, y, view;
};

class Glfw : public IGraphicLib
{
	public:
		Glfw(short, short);
		~Glfw(void);

		void	render(Data const &);
		void	getEvent(eDir *);
		std::list <int> *getEventPoll(void);

	private:
		void	_init(short, short);
		void	_stop(void);
		void	_setVerticesDraw(Data const &, int, dataInfo);
		void	_setVertice(vertexMap, Data const &, int, void	(*fct)(int, int , int , GLfloat *, Data const &, vertexMap));
		void	_printMiniMap(void);
		void	_printFloor(vertexMap src, Data const & data, int h);

		GLFWwindow	*_window;
		GLuint		*_program;
		GLint		*_mvp_location;
		vertexMap	*_vertices;
		std::map < int, int > _directionMap;
		std::map < int, int > _direction2Map;
		std::map < int, eDir > _interactionMap;
		std::list < int > _eventPoll;
};

extern "C"
{
	IGraphicLib	*createGraphicLib(short, short);
	void		deleteGraphicLib(IGraphicLib *);
}

#endif
