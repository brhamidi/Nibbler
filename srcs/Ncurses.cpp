/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ncurses.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:49:32 by msrun             #+#    #+#             */
/*   Updated: 2018/05/18 18:59:10 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ncurses.hpp"

Ncurses::~Ncurses(void)
{
	this->_stop();
}

Ncurses::Ncurses(void)
{
	this->_init();
}

void	Ncurses::_stop(void)
{
	endwin();
}

void	Ncurses::_init(void) 
{
	int row,col;

	initscr();
	cbreak();
	timeout(0);
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	getmaxyx(stdscr,row,col);
	start_color();
	init_pair(eNum::Blank + 1, COLOR_BLACK, COLOR_BLACK);
	init_pair(eNum::Wall + 1, COLOR_GREEN, COLOR_GREEN);
	init_pair(eNum::Snake + 1, COLOR_RED, COLOR_RED);
	init_pair(eNum::Food + 1, COLOR_CYAN, COLOR_CYAN);
	init_pair(eNum::Head + 1, COLOR_YELLOW, COLOR_YELLOW);
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

eDir	Ncurses::getEvent(void) const
{
	static eDir	direction = eDir::Left;
	int			c = -1;
	eDir		tmp;

	while((c = getch()) != ERR)
	{
		tmp = direction;
		if (c == eDir::Exit)
		{
			flushinp();
			return eDir::Exit;
		}
		switch(c)
		{
			case KEY_UP:
				direction = eDir::Up;
				break;
			case KEY_RIGHT:
				direction = eDir::Right;
				break;
			case KEY_DOWN:
				direction = eDir::Down;
				break;
			case KEY_LEFT:
				direction = eDir::Left;
				break;
			default:
				break;
		}
		if (direction % 2 == tmp % 2)
			direction = tmp;
		if (tmp != direction)
			break;
	}
	flushinp();
	return direction;
}

IGraphicLib	*createGraphicLib(void)
{
	return new Ncurses();
}

void	deleteGraphicLib(IGraphicLib *graphicLib)
{
	delete graphicLib;
}
