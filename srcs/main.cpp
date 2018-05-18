/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:22:27 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/18 18:59:05 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"
#include <ncurses.h>
#include <sys/time.h>
#include <ctime>
#include "Ncurses.hpp"
#include "IGraphicLib.hpp"
#include <dlfcn.h>

void	dlerror_wrapper(void)
{
	std::cerr << "Error: " << dlerror() << std::endl;
	exit(EXIT_FAILURE);
}

IGraphicLib	*getLib(void **dl_handle)
{
	*dl_handle = dlopen("Ncurses.so", RTLD_LAZY | RTLD_LOCAL);
	if (!*dl_handle)
		dlerror_wrapper();
	IGraphicLib *(*createGraphicLib)(void);
	createGraphicLib = (IGraphicLib *(*)(void)) dlsym(*dl_handle, "createGraphicLib");
	if (!createGraphicLib)
		dlerror_wrapper();
	IGraphicLib *library = createGraphicLib();
	return library;
}

void	deleteLib(IGraphicLib *library, void *dl_handle)
{
	dl_handle = dlopen("Ncurses.so", RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle)
		dlerror_wrapper();
	void (*deleteGraphicLib)(IGraphicLib *);
	deleteGraphicLib = (void (*)(IGraphicLib *)) dlsym(dl_handle, "deleteGraphicLib");
	if (!deleteGraphicLib)
		dlerror_wrapper();
	deleteGraphicLib(library);
	dlclose(dl_handle);
}

int		main(void)
{
	void	*dl_handle;
	struct timeval stop, start;
	GameCore & core = GameCore::getGame(150, 50);
	std::srand(std::time(nullptr));

	eDir	direction;
	IGraphicLib	*library = getLib(&dl_handle);
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
