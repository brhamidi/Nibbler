/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:13:32 by bhamidi           #+#    #+#             */
/*   Updated: 2018/06/07 15:44:38 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ncurses.h>
#include <iostream>

int		get_mode(const char ** choice, int len)
{
    int i;
    int x, y;

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, y, x);
    WINDOW * menuwin = newwin(len * 5, 20, y / 2 - len * 5, x / 2 - 20);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, TRUE);
	curs_set( 0 );
	noecho();

    int c;
    int current = 0;

    while(1)
    {
        for(i = 0; i < len; i++) {
            if(i == current)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 1, choice[i]);
            if (i == current)
                wattroff(menuwin, A_REVERSE);
        }

        c = wgetch(menuwin);
        switch(c)
        {
        case KEY_UP:
            current--;
            if(current < 0) current = len - 1;
            break;
        case KEY_DOWN:
            current++;
            if(current == len) current = 0;
            break;
        default:
            break;
        }

        if (c==10) break;
    }

    refresh();
    wrefresh(menuwin);
    endwin();
    return current;
}
