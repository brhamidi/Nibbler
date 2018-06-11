/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glfw.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:12:10 by msrun             #+#    #+#             */
/*   Updated: 2018/06/11 17:00:28 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Glfw.hpp"
#include <iostream>


Glfw::~Glfw(void)
{
	this->_stop();
}

static void	FillArray(GLfloat *array, float *src, int size)
{
	for (int i = 0; i < size; i++)
		array[i] = src[i];
}

Glfw::Glfw(short x, short y)
	: _window(NULL)
{
	this->_init(x, y);
	{
		float color[] = {
			0.502, 0.502, 0.502,   0.827, 0.827, 0.827,   0.184, 0.310, 0.310,   0.439, 0.502, 0.565,
			0.502, 0.502, 0.502,   0.827, 0.827, 0.827,   0.184, 0.310, 0.310,   0.439, 0.502, 0.565,
			0.502, 0.502, 0.502,   0.827, 0.827, 0.827,   0.184, 0.310, 0.310,   0.439, 0.502, 0.565,
			0.502, 0.502, 0.502,   0.827, 0.827, 0.827,   0.184, 0.310, 0.310,   0.439, 0.502, 0.565,
			0.502, 0.502, 0.502,   0.827, 0.827, 0.827,   0.184, 0.310, 0.310,   0.439, 0.502, 0.565,
			0.502, 0.502, 0.502,   0.827, 0.827, 0.827,   0.184, 0.310, 0.310,   0.439, 0.502, 0.565
	   	};
		FillArray(this->_WallColor, color, 48);
	}
	{
		float color[] = {
			0.764, 0.254, 0.254,	0.184, 0, 0.678,		0.184, 0, 0.678,		0.611, 0.050, 0.152,		
			0.764, 0.254, 0.254,	0.184, 0, 0.678,		0.184, 0, 0.678,		0.611, 0.050, 0.152,		
			0.764, 0.254, 0.254,	0.184, 0, 0.678,		0.184, 0, 0.678,		0.611, 0.050, 0.152,		
			0.611, 0.050, 0.152,	0.764, 0.254, 0.254,	0.611, 0.050, 0.152,	0.764, 0.254, 0.254
		};
		FillArray(this->_ObstacleColor, color, 48);
	}
	{
		float color[] = {
			0, 0.678, 0.141,	0.023, 0.356, 0.094,	0.023, 0.356, 0.352,	0.219, 0.356, 0.023,
			0, 0.678, 0.141,	0.023, 0.356, 0.094,	0.023, 0.356, 0.352,	0.219, 0.356, 0.023,
			0, 0.678, 0.141,	0.023, 0.356, 0.094,	0.023, 0.356, 0.352,	0.219, 0.356, 0.023,
			0, 0.678, 0.141,	0.023, 0.356, 0.094,	0.023, 0.356, 0.352,	0.219, 0.356, 0.023
		};
		FillArray(this->_SnakeColor, color, 48);
	}
	{
		float color[] = {
			0, 0.678, 0.141,	0.023, 0.356, 0.094,	0.023, 0.356, 0.352,	0.219, 0.356, 0.023,
			0, 0.678, 0.141,	0.023, 0.356, 0.094,	0.023, 0.356, 0.352,	0.219, 0.356, 0.023,
			0, 0.678, 0.141,	0.023, 0.356, 0.094,	0.023, 0.356, 0.352,	0.219, 0.356, 0.023,
			1, 0.917, 0.078, 	0.023, 0.356, 0.094,	0.023, 0.356, 0.352,		1, 0.917, 0.078,
		};
		FillArray(this->_SnakeHColor, color, 48);
	}
	{
		float color[] = {
			0.078, 0.125, 1,	0.313, 0.078, 1,	0.078, 0.533, 1,	0.121, 0.345, 0.917,
			0.078, 0.125, 1,	0.313, 0.078, 1,	0.078, 0.533, 1,	0.121, 0.345, 0.917,
			0.078, 0.125, 1,	0.313, 0.078, 1,	0.078, 0.533, 1,	0.121, 0.345, 0.917,
			0.078, 0.125, 1,	0.313, 0.078, 1,	0.078, 0.533, 1,	0.121, 0.345, 0.917
		};
		FillArray(this->_Snake2Color, color, 48);
	}
	{
		float color[] = {
			0.121, 0.917, 0.709,	0.572, 0.949, 0.850,	0.572, 0.901, 0.949,	0.572, 0.772, 0.949,
			0.121, 0.917, 0.709,	0.572, 0.949, 0.850,	0.572, 0.901, 0.949,	0.572, 0.772, 0.949,
			0.121, 0.917, 0.709,	0.572, 0.949, 0.850,	0.572, 0.901, 0.949,	0.572, 0.772, 0.949,
			0.121, 0.917, 0.709,	0.572, 0.949, 0.850,	0.572, 0.901, 0.949,	0.572, 0.772, 0.949
		};
		FillArray(this->_SnakeH2Color, color, 48);
	}
	{
		float color[] = {
			0.949, 0.572, 0.858,	0.356, 0.003, 0.270,	0.843, 0.415, 0.741,	0.749, 0.415, 0.843,
			0.949, 0.572, 0.858,	0.356, 0.003, 0.270,	0.843, 0.415, 0.741,	0.749, 0.415, 0.843,
			0.949, 0.572, 0.858,	0.356, 0.003, 0.270,	0.843, 0.415, 0.741,	0.749, 0.415, 0.843,
			0.949, 0.572, 0.858,	0.749, 0.415, 0.843,	0.949, 0.572, 0.858,	0.749, 0.415, 0.843
		};
		FillArray(this->_BonusColor, color, 48);
	}
	{
		float color[] = {
			0.960, 0.317, 0.301,	0.921, 0.023, 0,	0.811, 0.380, 0.266,	0.905, 0.050, 0.301,
			0.960, 0.317, 0.301,	0.921, 0.023, 0,	0.811, 0.380, 0.266,	0.905, 0.050, 0.301,
			0.960, 0.317, 0.301,	0.921, 0.023, 0,	0.811, 0.380, 0.266,	0.905, 0.050, 0.301,
			0.960, 0.317, 0.301,	0.921, 0.023, 0,	0.811, 0.380, 0.266,	0.905, 0.050, 0.301
		};
		FillArray(this->_FoodColor, color, 48);
	}

/*
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
*/

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

	this->_pickColor[0] = this->_WallColor;
	this->_pickColor[1] = this->_FoodColor;
	this->_pickColor[2] = this->_SnakeColor;
	this->_pickColor[3] = this->_SnakeHColor;
	this->_pickColor[4] = this->_ObstacleColor;
	this->_pickColor[5] = this->_SnakeH2Color;
	this->_pickColor[6] = this->_BonusColor;
	this->_pickColor[7] = this->_Snake2Color;

	this->_lengthObj[0] = 0;
	this->_lengthObj[1] = 10;
	this->_lengthObj[2] = 2;
	this->_lengthObj[3] = 3;
	this->_lengthObj[4] = 3;
	this->_lengthObj[5] = 20;
	this->_lengthObj[6] = 3;
	this->_lengthObj[7] = 4;
	this->_lengthObj[8] = 3;

	this->_printer[0] = &Glfw::_printUp;
	this->_printer[1] = &Glfw::_printRight;
	this->_printer[2] = &Glfw::_printDown;
	this->_printer[3] = &Glfw::_printLeft;
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

static void	checkDir(eDir & direction)
{
	if (direction > eDir::Left)
		direction = eDir::Up;
	else if (direction < eDir::Up)
		direction = eDir::Left;
}

static void	checkPossibleDir(eDir & direction, eDir src)
{
	if (direction % 2 == src % 2)
		direction = src;
}

void	Glfw::_checkEvent(eDir &direction, eDir tmp, std::map < int, int > map, int key) const
{
	static eDir	dir[4] = {eDir::Up, eDir::Right, eDir::Down, eDir::Left};

	if (direction == tmp && (map[key]))
	{
		direction =
			(direction + map[key] < 0) ?
			eDir::Left : ((direction + map[key] > 3) ?
					eDir::Up : dir[direction + map[key]]);
		checkDir(direction);
	}
}

void	Glfw::getEvent(eDir *direction)
{
	glfwPollEvents();

	eDir	tmp[2];
	int		key;

	tmp[0] = direction[0];
	tmp[1] = direction[1];

	while ((tmp[0] == direction[0] || tmp[1] == direction[1])  && this->_eventPoll.size() != 0)
	{
		key = *this->_eventPoll.begin();
		this->_eventPoll.pop_front();

		if (direction[3] != eDir::Space)
		{
			_checkEvent(direction[0], tmp[0], this->_directionMap, key);	//p1
			_checkEvent(direction[1], tmp[1], this->_direction2Map, key);	//p2
		}
		
		if (this->_interactionMap[key]) //check to change lib
			direction[2] = this->_interactionMap[key];

		else if (key == GLFW_KEY_SPACE) //check to un/pause
		{
			if (direction[3] == eDir::Space)
				direction[3] = eDir::Up;
			else
				direction[3] = eDir::Space;
		}
		checkPossibleDir(direction[0], tmp[0]);
		checkPossibleDir(direction[1], tmp[1]);
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
	vertice[(data._width < data._height ? 0 : 1)] = (src.x + x - ((data._width < data._height ? data._height : data._width) / 2)) * 0.1f * - 2 / (data._width < data._height ? 2 : 1) + (data._width < data._height ? 0 : 20);

	vertice[(data._width < data._height ? 1 : 0)] = (src.y + y - ((data._width < data._height ? data._height : data._width) / 2)) * 0.1f * (data._width < data._height ? 1 : -1) * -2 / (data._width < data._height ? 1 : 2) + (data._width < data._height ? 20 : 0);

	vertice[2] = z * 0;
}

static void	setVerticeSquareScore(int h, GLfloat *vertices, vertexMap src, float len, float offx, float offy)
{
	setScore(-len, -len,  h, &vertices[0], src, offx, offy);
	setScore(-len,  len,  h, &vertices[3], src, offx, offy);
	setScore(len,  len,  h, &vertices[6], src, offx, offy);
	setScore(len, -len,  h, &vertices[9], src, offx, offy);
}

static void	setVerticeSquare(Data const & data, GLfloat *vertices, vertexMap src, float len)
{
	setage(-len, -len,  0, &vertices[0], data, src);
	setage(-len,  len,  0, &vertices[3], data, src);
	setage(len,  len,  0, &vertices[6], data, src);
	setage(len, -len,  0, &vertices[9], data, src);
}

static void	setVerticesQuad(Data const & data, int h, GLfloat *vertices, vertexMap src,
	void	(*fct)(float, float , int , GLfloat *, Data const &, vertexMap))
{
	fct(-1, -1, -h, &vertices[0], data, src);
	fct(-1, -1,  h, &vertices[3], data, src);
	fct(-1,  1,  h, &vertices[6], data, src);
	fct(-1,  1, -h, &vertices[9], data, src); //left 


	fct(1, -1, -h, &vertices[12], data, src);
	fct(1, -1,  h, &vertices[15], data, src);
	fct(1,  1,  h, &vertices[18], data, src);
	fct(1,  1, -h, &vertices[21], data, src); // right

/*	fct(-1, -1, -h, &vertices[24], data, src);
	fct(-1, -1,  h, &vertices[27], data, src);
	fct(1, -1,  h, &vertices[30], data, src);
	fct(1, -1, -h, &vertices[33], data, src); //Up
*/
	fct(-1,  1, -h, &vertices[24], data, src);
	fct(-1,  1,  h, &vertices[27], data, src);
	fct(1,  1,  h, &vertices[30], data, src);
	fct(1,  1, -h, &vertices[33], data, src); //Down

	fct(-1, -1, -h, &vertices[36], data, src);
	fct(-1,  1, -h, &vertices[39], data, src);
	fct(1,  1, -h, &vertices[42], data, src);
	fct(1, -1, -h, &vertices[45], data, src); // Bot

/*	fct(-1, -1,  h, &vertices[36], data, src);
	fct(-1,  1,  h, &vertices[39], data, src);
	fct(1,  1,  h, &vertices[42], data, src);
	fct(1, -1,  h, &vertices[45], data, src); //Top
*/

}

static void	setFloorColorArray(GLfloat *dst, int x, int y, Data const & data, int size)
{
	for (int i = 0; i < 4 * size; i++)
	{
		dst[i * 3] = (y * 0.123475f) * (1 / (data._height * 0.123475f));
	   	dst[i * 3 + 1] = (x * 0.14879f) * (1 / (data._width * 0.14879f));
	   	dst[i * 3 + 2] = (y * 0.147893f) * (1 / (data._height * 0.147893f));
	}
}

void	Glfw::_printFloor(vertexMap src, Data const & data, int x, int y)
{
	src.y += 1;
	GLfloat vertices[12];
	setVerticeSquare(data, vertices, src, 1);

	GLfloat colors[12];
	setFloorColorArray(colors, x, y, data, 1);

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
				_setScoreVertice({h * 2 + 0.f, w * 2 + 0.f , 0.f, 0.f, 1.f}, 1, offx, offy);
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


void	Glfw::_setScoreVertice(vertexMap src, int h, float offx, float offy)
{
	src.y += 1;
	GLfloat vertices[12];
	setVerticeSquareScore(h, vertices, src, 1, offx, offy);
	GLfloat colors[] =
	{
		1,0,0, 0,1,0, 0,0,1, 0,0,0,
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void	Glfw::_setVertice(vertexMap src, Data const & data, int h, void	(*fct)(float, float , int , GLfloat *, Data const &, vertexMap), GLfloat* colors)
{
	src.y += 1;
	GLfloat vertices[48];
	setVerticesQuad(data, h, vertices, src, fct);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glDrawArrays(GL_QUADS, 0, 16);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}


void	Glfw::_printUp(Data const & data, int height, dataInfo infoPos)
{
	if (infoPos.h - 4 <= infoPos.y)
	{
		if (data._map[infoPos.h][infoPos.w] == eNum::Blank)
			this->_printFloor( {-(infoPos.x - infoPos.w) + data._width / 2 + 0.f, infoPos.view - infoPos.y + data._height + 0.f, 0.f, 0.f, 1.f}, data, infoPos.w, infoPos.h);
		else
			this->_setVertice( {-(infoPos.x - infoPos.w) + data._width / 2 + 0.f, infoPos.view - infoPos.y + data._height + 0.f, 0.f, 0.f, 1.f}, data, height, setage, this->_pickColor[data._map[infoPos.h][infoPos.w] - 1]);
	}
}

void	Glfw::_printDown(Data const & data, int height, dataInfo infoPos)
{
	if (infoPos.h + 4 >= infoPos.y)
	{
		if (data._map[infoPos.h][infoPos.w] == eNum::Blank)
			this->_printFloor( {(infoPos.x - infoPos.w) + data._width / 2 + 0.f,  data._height - infoPos.view + 6 + 0.f, 0.f, 0.f, 1.f}, data, infoPos.w, infoPos.h);
		else
			this->_setVertice( {(infoPos.x - infoPos.w) + data._width / 2 + 0.f,  data._height - infoPos.view + 6 + 0.f, 0.f, 0.f, 1.f}, data, height, setage, this->_pickColor[data._map[infoPos.h][infoPos.w] - 1]);
	}
}

void	Glfw::_printRight(Data const & data, int height, dataInfo infoPos)
{
	if (infoPos.w + 4 >= infoPos.x)
	{
		if (data._map[infoPos.h][infoPos.w] == eNum::Blank)
			this->_printFloor( {-(infoPos.y - infoPos.h) + data._width / 2 + 0.f, data._height - infoPos.view + 5 + 0.f, 0.f, 0.f, 1.f}, data, infoPos.w, infoPos.h);
		else
			this->_setVertice( {-(infoPos.y - infoPos.h) + data._width / 2 + 0.f, data._height - infoPos.view + 5 + 0.f, 0.f, 0.f, 1.f}, data, height, setage, this->_pickColor[data._map[infoPos.h][infoPos.w] - 1]);
	}
}

void	Glfw::_printLeft(Data const & data, int height, dataInfo infoPos)
{
	if (infoPos.w - 4 <= infoPos.x)
	{
		if (data._map[infoPos.h][infoPos.w] == eNum::Blank)
			this->_printFloor( {(infoPos.y - infoPos.h) + data._width / 2 + 0.f, data._height - (infoPos.x - infoPos.view) + 1 + 0.f, 0.f, 0.f, 1.f}, data, infoPos.w, infoPos.h);
		else
			this->_setVertice( {(infoPos.y - infoPos.h) + data._width / 2 + 0.f, data._height - (infoPos.x - infoPos.view) + 1 + 0.f, 0.f, 0.f, 1.f}, data, height, setage, this->_pickColor[data._map[infoPos.h][infoPos.w] - 1]);
	}
}

void	Glfw::_setVerticesDraw(Data const & data, int height, dataInfo infoPos)
{
	(this->*_printer[data._snakeDir])(data, height, infoPos);

	if (data._map[infoPos.h][infoPos.w] != eNum::Blank)
		this->_setVertice({infoPos.h + 0.f, infoPos.w + 0.f, 0.f, 0.f, 1.f}, data, 1, setForMiniMap, this->_pickColor[data._map[infoPos.h][infoPos.w] - 1]);
	else
	{
		static GLfloat colors[48];
		setFloorColorArray(colors, infoPos.w, infoPos.h, data, 4);
		this->_setVertice({infoPos.h + 0.f, infoPos.w + 0.f, 0.f, 0.f, 1.f}, data, 1, setForMiniMap, colors);
	}
}

void	Glfw::render(Data const &data)
{
	int x = 0;
	int y = 0;
	int view = 0;

	GLint windowWidth, windowHeight;
	glfwGetWindowSize(this->_window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	// Draw stuff
	glClearColor(0.5, 0.8, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();
	gluPerspective( 100, 1, 0.1, 100);

	glMatrixMode(GL_MODELVIEW_MATRIX);
	glTranslatef(0, -10, -20); //camera
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
	view = 0;
	this->_printScore(data._score);

	for (auto h = 0; h < data._height; h++)
	{
		if ((data._snakeDir == eDir::Up && h - 4 <= y) || (data._snakeDir == eDir::Down && h + 4 >= y))
			++view;
		else
			view = 0;
		for (auto w = 0; w < data._width; w++)
		{
			this->_setVerticesDraw(data, this->_lengthObj[data._map[h][w]], {h, w, x, y, view});
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
