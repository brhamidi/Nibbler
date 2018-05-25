/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:22:27 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/25 16:15:10 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"
#include <sys/time.h>
#include <ctime>
#include <cstring>
#include "IGraphicLib.hpp"
#include <dlfcn.h>

void	dlerror_wrapper(void)
{
	std::cerr << "Error: " << dlerror() << std::endl;
	exit(EXIT_FAILURE);
}

IGraphicLib	*getLib(void **dl_handle, short x, short y)
{
	*dl_handle = dlopen("lib3.so", RTLD_LAZY | RTLD_LOCAL);
	if (! *dl_handle)
		dlerror_wrapper();
	IGraphicLib *(*createGraphicLib)(short, short);
	createGraphicLib =
		(IGraphicLib *(*)(short, short)) dlsym(*dl_handle, "createGraphicLib");
	if (!createGraphicLib)
		dlerror_wrapper();
	return createGraphicLib(x, y);
}

void	deleteLib(IGraphicLib *library, void *dl_handle)
{
	void (*deleteGraphicLib)(IGraphicLib *);
	deleteGraphicLib = (void (*)(IGraphicLib *)) dlsym(dl_handle, "deleteGraphicLib");
	if (!deleteGraphicLib)
		dlerror_wrapper();
	deleteGraphicLib(library);
	dlclose(dl_handle);
}

int		usage(const char *filename)
{
	std::cerr << "Usage: " << filename <<
		" [ 10 <= X <= 170] [10 <= Y <= 70] [0 < Obstacle number < X * Y]" << std::endl;;
	return EXIT_FAILURE;
}

bool	str_is_digit(const char * str)
{
	if (! *str)
		return true;
	if (! std::isdigit(* str))
		return false;
	return str_is_digit(str + 1);
}

int		main(int ac, char *av[])
{
	std::srand(std::time(nullptr));
	int		x;
	int		y;
	int		obstacle = 0;

	if (ac != 3 && ac != 4)
		return usage(av[0]);
	if (std::strlen(av[1]) > 4 || std::strlen(av[2]) > 4
			|| ! str_is_digit(av[1]) || ! str_is_digit(av[2]))
		return usage(av[0]);
	x = std::atoi(av[1]);
	y = std::atoi(av[2]);
	if (ac == 4)
	{
		if (std::strlen(av[3]) > 4 || ! str_is_digit(av[2]) )
			return usage(av[0]);
		obstacle = std::atoi(av[3]);
		if ((x * y - (x * 2 + y * 2 + 4 + 1 )) <= obstacle )
			return usage(av[0]);
	}
	if (x < 10 || x > 170 || y < 10 || y > 70)
		return usage(av[0]);

	void			*dl_handle;
	struct timeval	stop, start;
	eDir			direction;
	IGraphicLib		*library = getLib(&dl_handle, x, y);
	int	accTime 	= 10;

	GameCore & 		core = GameCore::getGame(x, y, obstacle);
	while (1)
	{
		gettimeofday(&start, NULL);

		core.getData()._score += 5;
		std::cout << core.getData()._score << std::endl;

		direction = library->getEvent();

		if (direction == eDir::Exit)
		{
			deleteLib(library, dl_handle);
			break ;
		}
		if (!(core.moveSnake(direction)))
		{
			deleteLib(library, dl_handle);
			std::cout << "Dead\n";
			break;
		}

		library->render( core.getData() );

		gettimeofday(&stop, NULL);
		while (std::abs(stop.tv_usec - start.tv_usec) < (100000 - accTime))
			gettimeofday(&stop, NULL);
		if (accTime + 100 < 50000)
			accTime = core.getData()._score / 5;
	}
	return (0);
}
