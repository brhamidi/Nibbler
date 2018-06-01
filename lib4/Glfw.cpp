/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glfw.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:12:10 by msrun             #+#    #+#             */
/*   Updated: 2018/06/01 20:52:06 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Glfw.hpp"
#include <iostream>


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
	delete [] this->_vertices;
	//glfwDestroyWindow(this->_window);
	glfwTerminate();
}

void	key_callback(GLFWwindow* window, int key, int, int action, int)
{
	static std::list < int > *eventPoll = NULL;
	if (!eventPoll)
	{
		Glfw	*obj = (reinterpret_cast<Glfw*>(glfwGetWindowUserPointer(window)));
		eventPoll = obj->getEventPoll();
	}
	//segfault 
    if (action == GLFW_PRESS)
		eventPoll->push_back(key);
}

std::list < int > *Glfw::getEventPoll(void)
{
	return &this->_eventPoll;
}

void	Glfw::_init(short x, short y) 
{
	this->_vertices = new vertexMap[x * y * 4]();

	this->_directionMap[GLFW_KEY_RIGHT] = eDir::Right;
	this->_directionMap[GLFW_KEY_UP] = eDir::Up;
	this->_directionMap[GLFW_KEY_DOWN] = eDir::Down;
	this->_directionMap[GLFW_KEY_LEFT] = eDir::Left;

	this->_direction2Map[GLFW_KEY_D] = eDir::Right;
	this->_direction2Map[GLFW_KEY_W] = eDir::Up;
	this->_direction2Map[GLFW_KEY_S] = eDir::Down;
	this->_direction2Map[GLFW_KEY_A] = eDir::Left;

	this->_interactionMap[GLFW_KEY_1] = eDir::Lib1;
	this->_interactionMap[GLFW_KEY_2] = eDir::Lib2;
	this->_interactionMap[GLFW_KEY_3] = eDir::Lib3;
	this->_interactionMap[GLFW_KEY_DELETE] = eDir::Exit;

	if(!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		return ;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

	this->_window = glfwCreateWindow(x * 15, y * 15, "Nibbler", NULL, NULL);
	glfwSetWindowUserPointer(this->_window, this);

	if(this->_window == NULL)
	{
		std::cerr << "Failed to open GLFW window.\n";
		glfwTerminate();
		return ;
	}

	glfwMakeContextCurrent(this->_window);
	glfwSetKeyCallback(this->_window, key_callback);

	glEnable(GL_DEPTH_TEST); // Depth Testing
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void	Glfw::getEvent(eDir *direction)
{
	glfwPollEvents();

	eDir	tmp[2];
	int		key;

	tmp[0] = direction[0];
	tmp[1] = direction[1];
	while ( this->_eventPoll.size() != 0)
	{
		key = *this->_eventPoll.begin();
		this->_eventPoll.pop_front();

		if (direction[0] == tmp[0] && (this->_directionMap[key] || key == GLFW_KEY_UP))
			direction[0] = this->_directionMap[key];
		else if (direction[1] == tmp[1] && (this->_direction2Map[key] || key == GLFW_KEY_W))
			direction[1] = this->_direction2Map[key];
		else if (this->_interactionMap[key])
			direction[2] = this->_interactionMap[key];
		else if (key == GLFW_KEY_SPACE)
		{
			if (direction[3] == eDir::Space)
				direction[3] = eDir::Up;
			else
				direction[3] = eDir::Space;
		}
		if (direction[0] % 2 == tmp[0] % 2)
			direction[0] = tmp[0];
		if (direction[1] % 2 == tmp[1] % 2)
			direction[1] = tmp[1];
		if (tmp[0] != direction[0] && tmp[1] != direction[1])
			break;
	}
}

static void	setage(int x, int y, int z, GLfloat *vertice, Data const & data, vertexMap src)
{
	static float percent = (data._width * 1.f) / (data._height * 1.f);

	vertice[0] = ( ( ( ( (src.x / (data._width * 1.f) ) * 100.f ) * 2) - 100.0f + (x * (100.0f * (1.0f / data._width)) ) ) ) * percent;

	vertice[1] = ( ( ( (src.y / (data._height * 1.f) ) * 100.f ) * 2) - 100.0f + (y * (100.0f * (1.0f / data._height)) ) ) * -1.0f;

	vertice[2] = z;
}

void	Glfw::_setVertice(int pos, vertexMap src, Data const & data)
{
	GLfloat vertices[72];
	setage(-1, -1, -1, &vertices[0], data, src);
	setage(-1, -1,  1, &vertices[3], data, src);
	setage(-1,  1,  1, &vertices[6], data, src);
	setage(-1,  1, -1, &vertices[9], data, src);

	setage(1, -1, -1, &vertices[12], data, src);
	setage(1, -1,  1, &vertices[15], data, src);
	setage(1,  1,  1, &vertices[18], data, src);
	setage(1,  1, -1, &vertices[21], data, src);

	setage(-1, -1, -1, &vertices[24], data, src);
	setage(-1, -1,  1, &vertices[27], data, src);
	setage(1, -1,  1, &vertices[30], data, src);
	setage(1, -1, -1, &vertices[33], data, src);

	setage(-1,  1, -1, &vertices[36], data, src);
	setage(-1,  1,  1, &vertices[39], data, src);
	setage(1,  1,  1, &vertices[42], data, src);
	setage(1,  1, -1, &vertices[45], data, src);

	setage(-1, -1, -1, &vertices[48], data, src);
	setage(-1,  1, -1, &vertices[51], data, src);
	setage(1,  1, -1, &vertices[54], data, src);
	setage(1, -1, -1, &vertices[57], data, src);

	setage(-1, -1,  1, &vertices[60], data, src);
	setage(-1,  1,  1, &vertices[63], data, src);
	setage(1,  1,  1, &vertices[66], data, src);
	setage(1, -1,  1, &vertices[69], data, src);
	
	GLfloat colors[] =
	{
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
	};


		static float alpha = 0;
	//attempt to rotate cube
//	glRotatef(alpha, 0, 0, 1);

	/* We have a color array and a vertex array */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	/* Send data : 24 vertices */
	glDrawArrays(GL_QUADS, 0, 24);

	/* Cleanup states */
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

		alpha += 0.001;

}

void	Glfw::_setVerticesDraw(int pos, vertexMap src, Data const & data)
{
	this->_setVertice(pos, {src.x, src.y + 1, src.r, src.g, src.b}, data);
/*	this->_setVertice(pos + 1, {src.x, src.y, src.r, src.g, src.b}, data);
	this->_setVertice(pos + 2, {src.x + 1, src.y, src.r, src.g, src.b}, data);
	this->_setVertice(pos + 3, {src.x + 1, src.y + 1, src.r, src.g, src.b}, data);*/
//	glDrawArrays(GL_QUADS, pos, 4);
}

void	Glfw::render(Data const &data)
{
	(void)data;
	GLint windowWidth, windowHeight;
	glfwGetWindowSize(this->_window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	// Draw stuff
	glClearColor(0.5, 0.8, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();
	gluPerspective( 100, (double)windowWidth / (double)windowHeight, 0.1, 100);

	glMatrixMode(GL_MODELVIEW_MATRIX);
	glTranslatef(0, 0, -100); //camera ?
	for (auto h = 0; h < data._height; h++)
		for (auto w = 0; w < data._width; w++)
			if (data._map[h][w] == eNum::Snake ||data._map[h][w] == eNum::Wall || data._map[h][w] == eNum::Food)
				this->_setVerticesDraw(0, {w + 0.f, h + 0.f, 0.f, 0.f, 1.f}, data);

	// Update Screen
	glfwSwapBuffers(this->_window);

	// Check for any input, or window movement
	glfwPollEvents();
}

IGraphicLib	*createGraphicLib(short x, short y)
{
	return new Glfw(x, y);
}

void	deleteGraphicLib(IGraphicLib *graphicLib)
{
	delete graphicLib;
}
