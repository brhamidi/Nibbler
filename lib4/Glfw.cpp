/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glfw.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:12:10 by msrun             #+#    #+#             */
/*   Updated: 2018/06/01 14:05:53 by msrun            ###   ########.fr       */
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
	glfwTerminate();
}

void	key_callback(GLFWwindow* window, int key, int, int action, int)
{
	static std::list < int > *eventPoll = NULL;
	if (!eventPoll)
		eventPoll = (reinterpret_cast<Glfw*>(glfwGetWindowUserPointer(window)))->getEventPoll();
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

	static const char* vertex_shader_text =
		"uniform mat4 MVP;\n"
		"attribute vec3 vCol;\n"
		"attribute vec2 vPos;\n"
		"varying vec3 color;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
		"    color = vCol;\n"
		"}\n";
	static const char* fragment_shader_text =
		"varying vec3 color;\n"
		"void main()\n"
		"{\n"
		"    gl_FragColor = vec4(color, 1.0);\n"
		"}\n";

	GLFWwindow* window;
	GLuint vertex_buffer, vertex_shader, fragment_shader;
	this->_program = new GLuint();
	this->_mvp_location = new GLint();
	GLint vpos_location, vcol_location;
	if (!glfwInit())
		exit(-1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	glfwInit();
	window = glfwCreateWindow(x * 15, y * 15, "Nibbler", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(-1);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	this->_window = window;
	glfwSetWindowUserPointer(this->_window, this);
	glfwSwapInterval(1);
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);
	*this->_program = glCreateProgram();
	glAttachShader(*this->_program, vertex_shader);
	glAttachShader(*this->_program, fragment_shader);
	glLinkProgram(*this->_program);
	*this->_mvp_location = glGetUniformLocation(*this->_program, "MVP");
	vpos_location = glGetAttribLocation(*this->_program, "vPos");
	vcol_location = glGetAttribLocation(*this->_program, "vCol");
	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
			sizeof(float) * 5, (void*) 0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
			sizeof(float) * 5, (void*) (sizeof(float) * 2));

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

void	Glfw::_setVertice(int pos, vertexMap src, Data const & data)
{
	this->_vertices[pos] = {
		2.0f * ((data._width * 1.f) / (data._height * 1.f)) * src.x / (data._width * 1.f) - 1.f * ((data._width * 1.f) / (data._height * 1.f)),
		(2.0f * src.y / (data._height * 1.f) - 1.f) * -1.f,
		src.r, src.g, src.b};
}

void	Glfw::_setVerticesDraw(int pos, vertexMap src, Data const & data)
{
	this->_setVertice(pos, {src.x, src.y + 1, src.r, src.g, src.b}, data);
	this->_setVertice(pos + 1, {src.x, src.y, src.r, src.g, src.b}, data);
	this->_setVertice(pos + 2, {src.x + 1, src.y, src.r, src.g, src.b}, data);
	this->_setVertice(pos + 3, {src.x + 1, src.y + 1, src.r, src.g, src.b}, data);
	glDrawArrays(GL_QUADS, pos, 4);
}

void	Glfw::render(Data const &data)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexMap) * data._width * data._height * 4  , this->_vertices, GL_STATIC_DRAW);

	float ratio;
	int width, height;
	mat4x4 m, p, mvp;
	glfwGetFramebufferSize(this->_window, &width, &height);
	ratio = width / (float) height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	mat4x4_identity(m);
	//static float i = 1;
	//i += 0.01;
//	mat4x4_rotate_Z(m, m, (float) glfwGetTime());
	mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	mat4x4_mul(mvp, p, m);
	glUseProgram(*this->_program);
	glUniformMatrix4fv(*this->_mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);

	int tmp = 0;
	for (auto h = 0; h < data._height; h++)
	{
		for (auto w = 0; w < data._width; w++)
		{
			if (data._map[h][w] == eNum::Blank)
				this->_setVerticesDraw(tmp * 4, {w + 0.f, h + 0.f, 0.f, 0.f, 1.f}, data);
			if (data._map[h][w] == eNum::Wall)
				this->_setVerticesDraw(tmp * 4, {w + 0.f, h + 0.f, 1.f, 0.f, 0.f}, data);
			if (data._map[h][w] == eNum::Snake)
				this->_setVerticesDraw(tmp * 4, {w + 0.f, h + 0.f, 1.f, 0.f, 0.f}, data);
			if (data._map[h][w] == eNum::Head)
				this->_setVerticesDraw(tmp * 4, {w + 0.f, h + 0.f, 1.f, 1.f, 0.f}, data);
			if (data._map[h][w] == eNum::Food)
				this->_setVerticesDraw(tmp * 4, {w + 0.f, h + 0.f, 1.f, 0.f, 1.f}, data);
			if (data._map[h][w] == eNum::Obstacle)
				this->_setVerticesDraw(tmp * 4, {w + 0.f, h + 0.f, 1.f, 0.5f, 1.f}, data);
			tmp++;
		}
	}
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
