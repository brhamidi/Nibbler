/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:22:27 by bhamidi           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/05/17 12:47:39 by msrun            ###   ########.fr       */
=======
/*   Updated: 2018/05/17 12:49:05 by bhamidi          ###   ########.fr       */
>>>>>>> 40a456627306798455334ffeaac80dcfff8cf21e
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"
#include <ncurses.h>

int		main(void)
{
<<<<<<< HEAD
	GameCore & core = GameCore::getGame(200, 30);
=======
	std::srand(std::time(nullptr));

	GameCore const & core = GameCore::getGame(200, 30);
>>>>>>> 40a456627306798455334ffeaac80dcfff8cf21e
	(void)core;

	initscr();				/* start the curses mode */
	timeout(500);
	while (1)
	{
		int row,col;				/* to store the number of rows and *
									 * the number of colums of the screen */
		getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
		int c = getch();
		core.moveSnake(c);
	}
	endwin();

	return (0);
}
