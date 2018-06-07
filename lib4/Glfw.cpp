/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glfw.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:12:10 by msrun             #+#    #+#             */
/*   Updated: 2018/06/07 19:04:05 by msrun            ###   ########.fr       */
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

	this->_nibbler =
		"1111111000011001111111111100111111111110001100000000001111111110000111111111\n"
		"1111111110111000011100001110001110000111011100000000011100001110001110000111\n"
		"1110001110111000011100001110001110000111011100000000011100001100001110000111\n"
		"1110001110111000111111111100011111111110011100000000011111100000001111111111\n"
		"11100011101110011111111111001111111111100111000000001111111000000111111111\n"
		"1110001110111000011100001110001110000111011100000000011100001100001111111111\n"
		"1110001110111000011100001110001110000111011110000100011100001110001110000111\n"
		"0110001100110001111111111100111111111110011111111100011111111110001110000111\n"
		"0000000000000000000000000000000000000000010000000000000000000000001110000111\n";

	this->_score =
		"00011111111100111111111001111111100000111111111000011111111100000\n"
		"00111000011101110000111011100001110001110000111000111000011100000\n"
		"00111000011001110000110011100001110001110000111000111000011000011\n"
		"00111000000001110000000011100001110001111111111000111111000000011\n"
		"001111111111011100000000111000011100011111111000001111110000000000\n"
		"00000000011101110000110011100001110001111111111000111000011000000\n"
		"00011000011101110000111011100001110001110000111000111000011100011\n"
		"01111111111001111111110001111111100001110000111000111111111100011\n"
		"00000000000000000000000000000000000001110000111000000000000000000\n";

	this->_number[0] = 
		"0001111100\n"
		"0011000110\n"
		"0110000011\n"
		"0110000011\n"
		"0110000011\n"
		"0011000110\n"
		"0001111100\n";

	this->_number[1] = 
		"00001100\n"
		"00111100\n"
		"00001100\n"
		"00001100\n"
		"00001100\n"
		"00001100\n"
		"00111111\n";

	this->_number[2] = 
		"0011111110\n"
		"0110000011\n"
		"0000000011\n"
		"0011111110\n"
		"0110000000\n"
		"0110000000\n"
		"0111111111\n";

	this->_number[3] = 
		"0011111110\n"
		"0110000011\n"
		"0000000011\n"
		"0011111110\n"
		"0000000011\n"
		"0110000011\n"
		"0011111110\n";

	this->_number[4] = 
		"0110000000\n"
		"0110000110\n"
		"0110000110\n"
		"0110000110\n"
		"0111111111\n"
		"0000000110\n"
		"0000000110\n";

	this->_number[5] = 
		"011111111\n"
		"011000000\n"
		"011000000\n"
		"011111110\n"
		"000000011\n"
		"011000011\n"
		"001111110\n";

	this->_number[6] = 
		"0011111110\n"
		"0110000011\n"
		"0110000000\n"
		"0111111110\n"
		"0110000011\n"
		"0110000011\n"
		"0011111110\n";

	this->_number[7] = 
		"011111111\n"
		"011000011\n"
		"000001100\n"
		"000011000\n"
		"000110000\n"
		"000110000\n"
		"000110000\n";

	this->_number[8] = 
		"0011111110\n"
		"0110000011\n"
		"0110000011\n"
		"0011111110\n"
		"0110000011\n"
		"0110000011\n"
		"0011111110\n";

	this->_number[9] = 
		"0011111110\n"
		"0110000011\n"
		"0110000011\n"
		"0011111111\n"
		"0000000011\n"
		"0110000011\n"
		"0011111110\n";

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
	this->_directionMap[GLFW_KEY_LEFT] = -1;

	this->_direction2Map[GLFW_KEY_D] = 1;
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

static void	setage(float x, float y, int z, GLfloat *vertice, Data const & data, vertexMap src)
{
	static float percent = (data._width * 1.f) / (data._height * 1.f);

	vertice[0] = ( ( ( ( (src.x / (data._width * 1.f) ) * 10.f ) * 2) - 10.0f + (x * (10.0f * (1.0f / data._width)) ) ) ) * percent;

	vertice[2] = ( ( ( (src.y / (data._height * 1.f) ) * 10.f ) * 2) - 10.0f + (y * (10.0f * (1.0f / data._height)) ) );

	vertice[1] = (z * (10.0f * (1.0f / data._height)) * -1.0f) < 0? 0 : (z * (10.0f * (1.0f / data._height)) * -1.0f);
}

static void	setScore(float x, float y, int z, GLfloat *vertice, vertexMap src, float offx, float offy)
{
	vertice[0] = (y + src.y) / 20 - 23 + offy;

	vertice[1] = ((x + src.x) / 10 * -1.f) + 30 + offx;

	vertice[2] = z * 0;
}

static void	setForMiniMap(float x, float y, int z, GLfloat *vertice, Data const & data, vertexMap src)
{
	vertice[(data._width < data._height ? 0 : 1)] = (src.x + x - ((data._width < data._height ? data._height : data._width) / 2)) * 0.1f * -2 + (data._width < data._height ? 0 : 20);

	vertice[(data._width < data._height ? 1 : 0)] = (src.y + y - ((data._width < data._height ? data._height : data._width) / 2)) * 0.1f * (data._width < data._height ? 1 : -1) * -2 + (data._width < data._height ? 20 : 0);

	vertice[2] = z * 0;
}

static void	setVerticeSquareScore(int h, GLfloat *vertices, vertexMap src, float len, float offx, float offy)
{
	setScore(-len, -len,  h, &vertices[0], src, offx, offy);
	setScore(-len,  len,  h, &vertices[3], src, offx, offy);
	setScore(len,  len,  h, &vertices[6], src, offx, offy);
	setScore(len, -len,  h, &vertices[9], src, offx, offy);
}

static void	setVerticeSquare(Data const & data, int h, GLfloat *vertices, vertexMap src, float len)
{
	setage(-len, -len,  h, &vertices[0], data, src);
	setage(-len,  len,  h, &vertices[3], data, src);
	setage(len,  len,  h, &vertices[6], data, src);
	setage(len, -len,  h, &vertices[9], data, src);
}

static void	setVerticesQuad(Data const & data, int h, GLfloat *vertices, vertexMap src,
	void	(*fct)(float, float , int , GLfloat *, Data const &, vertexMap))
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
	setVerticeSquare(data, h, vertices, src, 0.9);

/*	static float r = 0, g = 0.5, b = 1;
	static bool rb = false, gb = true,bb = false;
	if (rb)
		r += 0.00001;
	else
		r -= 0.00001;
	if (r >= 1)
		r = false;
	else if (r <= 0)
		r = true;
	if (gb)
		g += 0.00001;
	else
		g -= 0.00001;
	if (g >= 1)
		g = false;
	else if (g <= 0)
		g = true;
	if (bb)
		b += 0.00001;
	else
		b -= 0.00001;
	if (b >= 1)
		b = false;
	else if (b <= 0)
		b = true;
*/


	GLfloat colors[] =
	{
		1, 0, 1,   0, 1, 1,   0.1, 0.5, 0.7,   0, 0, 1,
		0.502, 0.502, 0.502,   0.827, 0.827, 0.827,   0.184, 0.310, 0.310,   0.439, 0.502, 0.565, //gray
		0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1, // blue
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void	Glfw::_printString(std::string str, float offx, float offy)
{
	int w = 0;
	int h = 0;
	for (auto c : str)
	{
		if (c == '\n')
		{
			w = 0;
			h++;
		}
		else
		{
			if (c != '0')
				_setScoreVertice({h * 2 + 0.f, w * 2 + 0.f , 0.f, 0.f, 1.f}, 1, setForMiniMap, offx, offy);
			w++;
		}
	}
}

void	Glfw::_printScoreNumber(int score, float offx, float pos)
{
	if (score / 10 != 0)
		this->_printScoreNumber(score / 10, offx, pos - 1);
	this->_printString(this->_number[score % 10], offx, pos);
}

void	Glfw::_printScore(int score)
{
	this->_printString(this->_nibbler, 3, 0);
	this->_printString(this->_score, 0, 0);
	this->_printScoreNumber(score, 0, 6 + (std::to_string(score).length()));
}


void	Glfw::_setScoreVertice(vertexMap src, int h, void (*fct)(float, float , int , GLfloat *, Data const &, vertexMap), float offx, float offy)
{
	src.y += 1;
	GLfloat vertices[12];
	setVerticeSquareScore(h, vertices, src, 1, offx, offy);
	GLfloat colors[] =
	{
		1,0,0, 0,1,0, 0,0,1, 0,0,0,
		1, 0, 1,   0, 1, 1,   1, 1, 1,   0, 0, 1,
		0.502, 0.502, 0.502,   0.827, 0.827, 0.827,   0.184, 0.310, 0.310,   0.439, 0.502, 0.565, //gray
		0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1, // blue
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void	Glfw::_setVertice(vertexMap src, Data const & data, int h, void	(*fct)(float, float , int , GLfloat *, Data const &, vertexMap))
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
	for (auto h = 0; h < data._height && !x; h++)
		for (auto w = 0; w < data._width; w++)
		{
			if (data._map[h][w] == eNum::Head)
			{
				x = w;
				y = h;
				break;
			}
		}
	int view = 0;

	this->_printScore(data._score);

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
