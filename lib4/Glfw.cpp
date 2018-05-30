
#include "Glfw.hpp"

Glfw::~Glfw(void)
{
	this->_stop();
}

Glfw::Glfw(short x, short y)
	: _window(NULL)
{
	this->_init(x, y);
}

void	Glfw::_stop(void)
{
	glfwTerminate();
}

void	Glfw::_init(short x, short y) 
{
	glfwInit();
	_window = glfwCreateWindow(x * 15, y * 15, "Hello World", NULL, NULL);
	glfwMakeContextCurrent(_window);
}

void	Glfw::getEvent(eDir *) const
{
	;
}

void	Glfw::render(Data const &)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(_window);
}

IGraphicLib	*createGraphicLib(short x, short y)
{
	return new Glfw(x, y);
}

void	deleteGraphicLib(IGraphicLib *graphicLib)
{
	delete graphicLib;
}
