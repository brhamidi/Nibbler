/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:22:27 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/17 12:47:39 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"
#include <ncurses.h>

int		main(void)
{
	GameCore & core = GameCore::getGame(200, 30);
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
