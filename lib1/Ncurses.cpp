/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ncurses.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:49:32 by msrun             #+#    #+#             */
/*   Updated: 2018/05/25 19:59:45 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ncurses.hpp"

Ncurses::~Ncurses(void)
{
	this->_stop();
}

Ncurses::Ncurses(short x, short y)
{
//	this->_keyFunction = {{KEY_DC, eDir::Exit}, {'1', eDir::Lib1}, {'2', eDir::Lib2}, {'3', eDir::Lib3}};
	this->_init(x, y);
}

void	Ncurses::_stop(void)
{
	endwin();
}

void	Ncurses::_init(short, short) 
{
	initscr();
	cbreak();
	timeout(0);
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	start_color();
	init_pair(eNum::Blank + 1, COLOR_BLACK, COLOR_BLACK);
	init_pair(eNum::Wall + 1, COLOR_GREEN, COLOR_GREEN);
	init_pair(eNum::Snake + 1, COLOR_RED, COLOR_RED);
	init_pair(eNum::Food + 1, COLOR_CYAN, COLOR_CYAN);
	init_pair(eNum::Head + 1, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(eNum::Obstacle + 1, COLOR_WHITE, COLOR_WHITE);
}

void	Ncurses::render(Data const & data) const
{
	for (auto h = 0; h < data._height; h++)
	{
		for (auto w = 0; w < data._width; w++)
		{
			attron(COLOR_PAIR(data._map[h][w] + 1));
			mvprintw(h, w * 2, "  ");
		}
	}
	refresh();
}

void 	Ncurses::getEvent(eDir *direction) const
{
	int			c = eDir::Error;
	eDir		tmp[2];

	tmp[0] = direction[0];
	tmp[1] = direction[1];
	while((c = getch()) != ERR)
	{
		if (!direction[2])
			switch (c)
			{
				case KEY_DC: direction[2] = eDir::Exit; break;
				case '1': direction[2] = eDir::Lib1; break;
				case '2': direction[2] = eDir::Lib2; break;
				case '3': direction[2] = eDir::Lib3; break;
				default: break;
			}
		if (tmp[0] != direction[0] && tmp[1] != direction[1])
			break;
		if (tmp[0] == direction[0])
		{
			tmp[0] = direction[0];
			switch(c)
			{
				case KEY_UP:
					direction[0] = eDir::Up;
					break;
				case KEY_RIGHT:
					direction[0] = eDir::Right;
					break;
				case KEY_DOWN:
					direction[0] = eDir::Down;
					break;
				case KEY_LEFT:
					direction[0] = eDir::Left;
					break;
				default:
					break;
			}
			if (direction[0] % 2 == tmp[0] % 2)
				direction[0] = tmp[0];
		}
		if (tmp[0] == direction[0])
		{
			tmp[0] = direction[0];
			switch(c)
			{
				case 'w':
					direction[1] = eDir::Up;
					break;
				case 'd':
					direction[1] = eDir::Right;
					break;
				case 's':
					direction[1] = eDir::Down;
					break;
				case 'a':
					direction[1] = eDir::Left;
					break;
				default:
					break;
			}
			if (direction[1] % 2 == tmp[1] % 2)
				direction[1] = tmp[1];
		}
	}
	flushinp();
}

IGraphicLib	*createGraphicLib(short x, short y)
{
	return new Ncurses(x, y);
}

void	deleteGraphicLib(IGraphicLib *graphicLib)
{
	delete graphicLib;
}
