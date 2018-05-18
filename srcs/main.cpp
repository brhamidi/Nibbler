/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:22:27 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/18 13:59:36 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"
#include <ncurses.h>
#include <sys/time.h>
#include <ctime>

int		main(void)
{
	GameCore & core = GameCore::getGame(150, 50);
	std::srand(std::time(nullptr));

	int c;
	int direction;
	while (1)
	{
		initscr();				/* start the curses mode */
		cbreak();
		timeout(0);
		noecho();
		keypad(stdscr, TRUE);
		//curs_set(0);
		struct timeval stop, start;
		gettimeofday(&start, NULL);
		int row,col;				/* to store the number of rows and *
									 * the number of colums of the screen */
		getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
		int	ctrash;
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
			break ;
		}
		flushinp();
	/*	switch(c)
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
				direction = -1;
				break;
		}*/
		if (!(core.moveSnake(direction)))
		{
			endwin();
			std::cout << "Dead\n";
			break;
		}
		gettimeofday(&stop, NULL);
		while (std::abs(stop.tv_usec - start.tv_usec) < 50000)
		{
			gettimeofday(&stop, NULL);
		}
		endwin();
		system("clear");
		core._printMap();
	}
	//core._printMap();

	return (0);
}
