/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ncurses.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:49:32 by msrun             #+#    #+#             */
/*   Updated: 2018/05/18 14:48:11 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ncurses.hpp"

Ncurses::Ncurses(void)
{
	initscr();
	cbreak();
	timeout(0);
	noecho();
	keypad(stdscr, TRUE);
	//curs_set(0);
	int row,col;
	getmaxyx(stdscr,row,col);
}

Ncurses::~Ncurses(void)
{
}

int		Ncurses::printMap(Data & data)
{
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_RED);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
	init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
	for (auto h = 0; h < data._height; h++)
	{
		for (auto w = 0; w < data._width; w++)
		{
			attron(COLOR_PAIR(data._map[h][w] + 1));
			mvprintw(h, w * 2, "  ");
		}
	}
	//refresh();
	//std::cout << std::endl;
	int c;
	static int direction = 3;

	int	ctrash = -1;
	while((ctrash = getch()) != ERR)
	{
		int tmp = direction;
		if (ctrash == 32)
			break ;
		switch(ctrash)
		{
			case KEY_UP:
				direction = 0;
				break;
			case KEY_RIGHT:
				direction = 1;
				break;
			case KEY_DOWN:
				direction = 2;
				break;
			case KEY_LEFT:
				direction = 3;
				break;
			default:
				break;
		}
		if (direction % 2 == tmp % 2)
			direction = tmp;
		if (tmp != direction)
		{
			c = ctrash;
			break;
		}
	}
	if (ctrash == 32)
	{
		endwin();
		return -2;
	}
	flushinp();
	return direction;
}
