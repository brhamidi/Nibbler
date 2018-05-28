
#ifndef SFML_HPP
# define SFML_HPP

# include "IGraphicLib.hpp"
#include <GLFW/glfw3.h>

# define VALUE	15
# define MENU	20

class Glfw : public IGraphicLib
{
	public:
		Glfw(short, short);
		~Glfw(void);

		void	render(Data const &) const;
		eDir	getEvent(void) const;

	private:
		void	_init(short, short);
		void	_stop(void);

		GLFWwindow* _window;

};

extern "C"
{
	IGraphicLib	*createGraphicLib(short, short);
	void		deleteGraphicLib(IGraphicLib *);
}

#endif
