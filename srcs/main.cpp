/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:22:27 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/21 19:33:56 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"
#include <sys/time.h>
#include <ctime>
#include "IGraphicLib.hpp"
#include <dlfcn.h>

void	dlerror_wrapper(void)
{
	std::cerr << "Error: " << dlerror() << std::endl;
	exit(EXIT_FAILURE);
}

IGraphicLib	*getLib(void **dl_handle)
{
	*dl_handle = dlopen("lib1.so", RTLD_LAZY | RTLD_LOCAL);
	if (! *dl_handle)
		dlerror_wrapper();
	IGraphicLib *(*createGraphicLib)(void);
	createGraphicLib = (IGraphicLib *(*)(void)) dlsym(*dl_handle, "createGraphicLib");
	if (!createGraphicLib)
		dlerror_wrapper();
	return createGraphicLib();
}

void	deleteLib(IGraphicLib *library, void *dl_handle)
{
	dl_handle = dlopen("lib1.so", RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle)
		dlerror_wrapper();
	void (*deleteGraphicLib)(IGraphicLib *);
	deleteGraphicLib = (void (*)(IGraphicLib *)) dlsym(dl_handle, "deleteGraphicLib");
	if (!deleteGraphicLib)
		dlerror_wrapper();
	deleteGraphicLib(library);
	dlclose(dl_handle);
}

int		usage(const char *filename)
{
	std::cerr << "Usage: " << filename << " [ 10 <= X <= 170] [10 <= Y <= 70]" << std::endl;;
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
	int x;
	int y;

	if (ac != 3)
		return usage(av[0]);
	if (strlen(av[1]) > 4 || strlen(av[2]) > 4
			|| ! str_is_digit(av[1]) || ! str_is_digit(av[2]))
		return usage(av[0]);
	x = std::atoi(av[1]);
	y = std::atoi(av[2]);
	if (x < 10 || x > 170 || y < 10 || y > 70)
		return usage(av[0]);

	void			*dl_handle;
	struct timeval	stop, start;
	eDir			direction;
	IGraphicLib		*library = getLib(&dl_handle);

	GameCore & 		core = GameCore::getGame(x, y);
	std::srand(std::time(nullptr));
	while (1)
	{
		gettimeofday(&start, NULL);

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
		while (std::abs(stop.tv_usec - start.tv_usec) < 100000)
			gettimeofday(&stop, NULL);
	}
	return (0);
}
