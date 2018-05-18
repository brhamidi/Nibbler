/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:22:27 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/18 18:05:07 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"
#include <ncurses.h>
#include <sys/time.h>
#include <ctime>
#include "Ncurses.hpp"
#include "IGraphicLib.hpp"

int		main(void)
{
	struct timeval stop, start;
	GameCore & core = GameCore::getGame(150, 50);
	std::srand(std::time(nullptr));

	eDir	direction;
	IGraphicLib	*ncur = new Ncurses();
	while (1)
	{
		gettimeofday(&start, NULL);

		direction = ncur->getEvent();

		if (direction == eDir::Exit)
		{
			delete ncur;
			break ;
		}
		if (!(core.moveSnake(direction)))
		{
			delete ncur;
			std::cout << "Dead\n";
			break;
		}

		ncur->render( core.getData() );

		gettimeofday(&stop, NULL);
		while (std::abs(stop.tv_usec - start.tv_usec) < 100000)
			gettimeofday(&stop, NULL);
	}
	return (0);
}
