/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:22:27 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/18 16:54:04 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"
#include <ncurses.h>
#include <sys/time.h>
#include <ctime>
#include "Ncurses.hpp"

int		main(void)
{
	struct timeval stop, start;
	GameCore & core = GameCore::getGame(150, 50);
	std::srand(std::time(nullptr));

	Ncurses ncur;
	int direction = ncur.printMap(core.getData());
	while (1)
	{
		gettimeofday(&start, NULL);

		if (!(core.moveSnake(direction)))
		{
			std::cout << "Dead\n";
			endwin();
			break;
		}

		direction = ncur.printMap(core.getData());
		if (direction == -2)
			break ;

		gettimeofday(&stop, NULL);
		while (std::abs(stop.tv_usec - start.tv_usec) < 100000)
			gettimeofday(&stop, NULL);
	}
	return (0);
}
