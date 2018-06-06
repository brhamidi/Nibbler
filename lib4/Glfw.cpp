/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glfw.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:12:10 by msrun             #+#    #+#             */
/*   Updated: 2018/06/06 17:13:04 by msrun            ###   ########.fr       */
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
	glfwDestroyWindow(this->_window);
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

	this->_directionMap[GLFW_KEY_RIGHT] = 1;
//	this->_directionMap[GLFW_KEY_UP] = eDir::Up;
//	this->_directionMap[GLFW_KEY_DOWN] = eDir::Down;
	this->_directionMap[GLFW_KEY_LEFT] = -1;

	this->_direction2Map[GLFW_KEY_D] = 1;
//	this->_direction2Map[GLFW_KEY_W] = eDir::Up;
//	this->_direction2Map[GLFW_KEY_S] = eDir::Down;
	this->_direction2Map[GLFW_KEY_A] = -1;

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

	this->_window = glfwCreateWindow(2000, 700, "Nibbler", NULL, NULL);
	glfwSetWindowUserPointer(this->_window, this);

	if(this->_window == NULL)
	{
		std::cerr << "Failed to open GLFW window.\n";
		glfwTerminate();
		return ;
	}

	glfwMakeContextCurrent(this->_window);
	glfwSetKeyCallback(this->_window, key_callback);

	glEnable(GL_DEPTH_TEST); // profondeur
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
	static eDir	dir[4] = {eDir::Up, eDir::Right, eDir::Down, eDir::Left};
	while ( this->_eventPoll.size() != 0)
	{
		key = *this->_eventPoll.begin();
		this->_eventPoll.pop_front();

		if (direction[0] == tmp[0] && (this->_directionMap[key]))
		{
			direction[0] =
				(direction[0] + this->_directionMap[key] < 0) ?
				   	eDir::Left : ((direction[0] + this->_directionMap[key] > 3) ?
						   	eDir::Up : dir[direction[0] + this->_directionMap[key]]);
			if (direction[0] > eDir::Left)
				direction[0] = eDir::Up;
			else if (direction[0] < eDir::Up)
				direction[0] = eDir::Left;
		}
		else if (direction[1] == tmp[1] && (this->_direction2Map[key]))
		{
			direction[1] =
				(direction[1] + this->_direction2Map[key] < 0) ?
				eDir::Left : ((direction[1] + this->_direction2Map[key] > 3) ?
				eDir::Up : dir[direction[1] + this->_direction2Map[key]]);
			if (direction[1] > eDir::Left)
				direction[1] = eDir::Up;
			else if (direction[1] < eDir::Up)
				direction[1] = eDir::Left;
		}
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

	vertice[0] = ( ( ( ( (src.x / (data._width * 1.f) ) * 10.f ) * 2) - 10.0f + (x * (10.0f * (1.0f / data._width)) ) ) ) * percent;

	vertice[2] = ( ( ( (src.y / (data._height * 1.f) ) * 10.f ) * 2) - 10.0f + (y * (10.0f * (1.0f / data._height)) ) );

	vertice[1] = (z * (10.0f * (1.0f / data._height)) * -1.0f) < 0? 0 : (z * (10.0f * (1.0f / data._height)) * -1.0f);
}

static void	setForMiniMap(int x, int y, int z, GLfloat *vertice, Data const & data, vertexMap src)
{
	vertice[(data._width < data._height ? 0 : 1)] = (src.x + x - ((data._width < data._height ? data._height : data._width) / 2)) * 0.1f * 2 + (data._width < data._height ? 0 : 20);

	vertice[(data._width < data._height ? 1 : 0)] = (src.y + y - ((data._width < data._height ? data._height : data._width) / 2)) * 0.1f * (data._width < data._height ? 1 : -1) * 2 + (data._width < data._height ? 20 : 0);

	vertice[2] = z * 0;
}

static void	setVerticeFloor(Data const & data, int h, GLfloat *vertices, vertexMap src)
{
	setage(-1, -1,  h, &vertices[0], data, src);
	setage(-1,  1,  h, &vertices[3], data, src);
	setage(1,  1,  h, &vertices[6], data, src);
	setage(1, -1,  h, &vertices[9], data, src);
}

static void	setVerticesQuad(Data const & data, int h, GLfloat *vertices, vertexMap src,
	void	(*fct)(int, int , int , GLfloat *, Data const &, vertexMap))
{
	fct(-1, -1, -h, &vertices[0], data, src);
	fct(-1, -1,  h, &vertices[3], data, src);
	fct(-1,  1,  h, &vertices[6], data, src);
	fct(-1,  1, -h, &vertices[9], data, src);

	fct(1, -1, -h, &vertices[12], data, src);
	fct(1, -1,  h, &vertices[15], data, src);
	fct(1,  1,  h, &vertices[18], data, src);
	fct(1,  1, -h, &vertices[21], data, src);

	fct(-1, -1, -h, &vertices[24], data, src);
	fct(-1, -1,  h, &vertices[27], data, src);
	fct(1, -1,  h, &vertices[30], data, src);
	fct(1, -1, -h, &vertices[33], data, src);

	fct(-1,  1, -h, &vertices[36], data, src);
	fct(-1,  1,  h, &vertices[39], data, src);
	fct(1,  1,  h, &vertices[42], data, src);
	fct(1,  1, -h, &vertices[45], data, src);

	fct(-1, -1, -h, &vertices[48], data, src);
	fct(-1,  1, -h, &vertices[51], data, src);
	fct(1,  1, -h, &vertices[54], data, src);
	fct(1, -1, -h, &vertices[57], data, src);

	fct(-1, -1,  h, &vertices[60], data, src);
	fct(-1,  1,  h, &vertices[63], data, src);
	fct(1,  1,  h, &vertices[66], data, src);
	fct(1, -1,  h, &vertices[69], data, src);
}

void	Glfw::_printFloor(vertexMap src, Data const & data, int h)
{
	src.y += 1;
	GLfloat vertices[12];
	setVerticeFloor(data, h, vertices, src);
	GLfloat colors[] =
	{
		0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void	Glfw::_setVertice(vertexMap src, Data const & data, int h, void	(*fct)(int, int , int , GLfloat *, Data const &, vertexMap))
{
	src.y += 1;
	GLfloat vertices[72];
	setVerticesQuad(data, h, vertices, src, fct);
	GLfloat colors[] =
	{
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void	Glfw::_setVerticesDraw(Data const & data, int height, dataInfo infoPos)
{
	eDir snakeDir = data._snakeDir;

	if (snakeDir == eDir::Up && infoPos.h - 4 <= infoPos.y)
	{
		if (data._map[infoPos.h][infoPos.w] == eNum::Blank)
			this->_printFloor( {-(infoPos.x - infoPos.w) + data._width / 2 + 0.f, infoPos.view - infoPos.y + data._height + 0.f, 0.f, 0.f, 1.f}, data, height);
		else
			this->_setVertice( {-(infoPos.x - infoPos.w) + data._width / 2 + 0.f, infoPos.view - infoPos.y + data._height + 0.f, 0.f, 0.f, 1.f}, data, height, setage);
	}
	else if (snakeDir == eDir::Down && infoPos.h + 4 >= infoPos.y)
	{
		if (data._map[infoPos.h][infoPos.w] == eNum::Blank)
			this->_printFloor( {(infoPos.x - infoPos.w) + data._width / 2 + 0.f,  data._height - infoPos.view + 6 + 0.f, 0.f, 0.f, 1.f}, data, height);
		else
			this->_setVertice( {(infoPos.x - infoPos.w) + data._width / 2 + 0.f,  data._height - infoPos.view + 6 + 0.f, 0.f, 0.f, 1.f}, data, height, setage);
	}
	else if (snakeDir == eDir::Right && infoPos.w + 4 >= infoPos.x)
	{
		if (data._map[infoPos.h][infoPos.w] == eNum::Blank)
			this->_printFloor( {-(infoPos.y - infoPos.h) + data._width / 2 + 0.f, data._height - infoPos.view + 5 + 0.f, 0.f, 0.f, 1.f}, data, height);
		else
			this->_setVertice( {-(infoPos.y - infoPos.h) + data._width / 2 + 0.f, data._height - infoPos.view + 5 + 0.f, 0.f, 0.f, 1.f}, data, height, setage);
	}
	else if (snakeDir == eDir::Left && infoPos.w - 4 <= infoPos.x)
	{
		if (data._map[infoPos.h][infoPos.w] == eNum::Blank)
			this->_printFloor( {(infoPos.y - infoPos.h) + data._width / 2 + 0.f, data._height - (infoPos.x - infoPos.view) + 1 + 0.f, 0.f, 0.f, 1.f}, data, height);
		else
			this->_setVertice( {(infoPos.y - infoPos.h) + data._width / 2 + 0.f, data._height - (infoPos.x - infoPos.view) + 1 + 0.f, 0.f, 0.f, 1.f}, data, height, setage);
	}

	if (data._map[infoPos.h][infoPos.w] != eNum::Blank)
		this->_setVertice({infoPos.h + 0.f, infoPos.w + 0.f, 0.f, 0.f, 1.f}, data, 1, setForMiniMap);
}

void	Glfw::render(Data const &data)
{
	GLint windowWidth, windowHeight;
	glfwGetWindowSize(this->_window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	// Draw stuff
	glClearColor(0.5, 0.8, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();
	gluPerspective( 100, 1/*(double)windowWidth / (double)windowHeight*/, 0.1, 100);

	glMatrixMode(GL_MODELVIEW_MATRIX);
	glTranslatef(0, -10, -20); //camera ?
	int x = 0;
	int y = 0;
	int x2 = 0;
	int y2 = 0;
	for (auto h = 0; h < data._height && (!x || !x2); h++)
		for (auto w = 0; w < data._width; w++)
		{
			if (data._map[h][w] == eNum::Head2)
			{
				x2 = w;
				y2 = h;
				break;
			}
			if (data._map[h][w] == eNum::Head)
			{
				x = w;
				y = h;
				break;
			}
		}
/*	for (int h = -100; h < 100; h++)
	{
		for (int w = -100; w < 100; w++)
		{
			this->_printFloor({h + 0.f, w + 0.f, 0, 0, 0}, data, 1);
		}
	}*/
	int view = 0;
	for (auto h = 0; h < data._height; h++)
	{
		if ((data._snakeDir == eDir::Up && h - 4 <= y) || (data._snakeDir == eDir::Down && h + 4 >= y))
			++view;
		else
			view = 0;
		for (auto w = 0; w < data._width; w++)
		{
			if (data._map[h][w] == eNum::Wall)
				this->_setVerticesDraw(data, 10, {h, w, x, y, view});
			else 
				this->_setVerticesDraw(data, 1, {h, w, x, y, view});
			if (data._snakeDir == eDir::Left && w - 4 <= x)
				++view;
			else if (data._snakeDir == eDir::Right && w + 4 >= x)
				++view;
		}
	}
	x = x2;
	y = y2;
	view = 0;
/*	for (auto h = 0; h < data._height; h++)
	{
		if ((data._snakeDir2 == eDir::Up && h - 4 <= y) || (data._snakeDir2 == eDir::Down && h + 4 >= y))
			++view;
		else
			view = 0;
		for (auto w = 0; w < data._width; w++)
		{
			if (data._map[h][w] == eNum::Wall)
				this->_setVerticesDraw(data, 10, {h, w, x, y, view}, true);
			if (data._map[h][w] == eNum::Head || data._map[h][w] == eNum::Snake || data._map[h][w] == eNum::Food)
				this->_setVerticesDraw(data, 1, {h, w, x, y, view}, true);
			if (data._snakeDir2 == eDir::Left && w - 4 <= x)
				++view;
			else if (data._snakeDir2 == eDir::Right && w + 4 >= x)
				++view;
		}
	}
*/
	// Update Screen
	glfwSwapBuffers(this->_window);
}

IGraphicLib	*createGraphicLib(short x, short y)
{
	return new Glfw(x, y);
}

void	deleteGraphicLib(IGraphicLib *graphicLib)
{
	delete graphicLib;
}
