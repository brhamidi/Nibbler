/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glfw.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:12:15 by msrun             #+#    #+#             */
/*   Updated: 2018/06/01 15:13:34 by msrun            ###   ########.fr       */
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
		void	_setVerticesDraw(int pos, vertexMap , Data const &);
		void	_setVertice(int pos, vertexMap , Data const &);

		GLFWwindow	*_window;
		GLuint		*_program;
		GLint		*_mvp_location;
		vertexMap	*_vertices;
		std::map < int, eDir > _directionMap;
		std::map < int, eDir > _direction2Map;
		std::map < int, eDir > _interactionMap;
		std::list < int > _eventPoll;
};

extern "C"
{
	IGraphicLib	*createGraphicLib(short, short);
	void		deleteGraphicLib(IGraphicLib *);
}

#endif
