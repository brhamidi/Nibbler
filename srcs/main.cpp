/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:22:27 by bhamidi           #+#    #+#             */
/*   Updated: 2018/06/11 16:36:10 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameCore.hpp"
#include <sys/time.h>
#include <ctime>
#include <cstring>
#include "IGraphicLib.hpp"
#include "IAudioLib.hpp"
#include <dlfcn.h>
#include <unistd.h>
#include <exception>

const char *libTab [4] = {
	"lib4.so",
	"lib2.so",
	"lib3.so"
};

const char *modeTab [2] = {
	"Single Player",
	"Multi Player"
};

const char *libNameTab [3] = {
	"OpenGl",
	"SDL",
	"SFML"
};

int		get_mode(const char ** choice, int len);

int		usage(const char *filename)
{
	std::cerr << "Usage: " << filename <<
		" [ 15 <= X <= 70] [15 <= Y <= 50] [0 < Obstacle number < X * Y]" << std::endl;;
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

int		arg(int ac, char **av, int *x, int *y, int *obstacle)
{
	if (ac != 3 && ac != 4)
		return usage(av[0]);
	if (std::strlen(av[1]) > 4 || std::strlen(av[2]) > 4
			|| ! str_is_digit(av[1]) || ! str_is_digit(av[2]))
		return usage(av[0]);
	*x = std::atoi(av[1]);
	*y = std::atoi(av[2]);
	if (ac == 4)
	{
		if (std::strlen(av[3]) > 4 || ! str_is_digit(av[2]) )
			return usage(av[0]);
		*obstacle = std::atoi(av[3]);
		if ((*x * *y - (*x * 2 + *y * 2 + 4 + 1 )) <= *obstacle )
			return usage(av[0]);
	}
	if (*x < 15 || *x >70  || *y < 15 || *y > 50)
		return usage(av[0]);
	return (0);
}

void	dlerror_wrapper(const std::string msg)
{
	std::cerr << "dlerror() " << dlerror() << std::endl;
	throw (std::runtime_error(msg));
}

IGraphicLib	*getLib(void **dl_handle, short x, short y, const char *libname)
{
	*dl_handle = dlopen(libname, RTLD_LAZY | RTLD_LOCAL);
	if (! *dl_handle)
		dlerror_wrapper("failed to open library");
	IGraphicLib *(*createGraphicLib)(short, short);
	createGraphicLib =
		(IGraphicLib *(*)(short, short)) dlsym(*dl_handle, "createGraphicLib");
	if (!createGraphicLib)
		dlerror_wrapper("failed to load symbol");
	return createGraphicLib(x, y);
}

void	deleteLib(IGraphicLib *library, void *dl_handle)
{
	void (*deleteGraphicLib)(IGraphicLib *);
	deleteGraphicLib = (void (*)(IGraphicLib *)) dlsym(dl_handle, "deleteGraphicLib");
	if (!deleteGraphicLib)
		dlerror_wrapper("failed to load symbol");
	deleteGraphicLib(library);
	dlclose(dl_handle);
}

void	deleteAudioLib(IAudioLib *library, void *dl_handle)
{
	void (*deleteAudioLib)(IAudioLib *);
	deleteAudioLib = (void (*)(IAudioLib *)) dlsym(dl_handle, "deleteAudioLib");
	if (!deleteAudioLib)
		dlerror_wrapper("failed to load symbol");
	deleteAudioLib(library);
	dlclose(dl_handle);
}

IAudioLib	*getAudioLib(void **dl_handle)
{
	*dl_handle = dlopen("lib5.so", RTLD_LAZY | RTLD_LOCAL);
	if (! *dl_handle)
		dlerror_wrapper("failed to open library");
	IAudioLib *(*createAudioLib)(void);
	createAudioLib =
		(IAudioLib *(*)(void)) dlsym(*dl_handle, "createAudioLib");
	if (!createAudioLib)
		dlerror_wrapper("failed to load symbol");
	return createAudioLib();
}

int		main(int ac, char *av[])
{
	std::srand(std::time(nullptr));
	int				x;
	int				y;
	int				obstacle = 0;
	unsigned short	custom = 0;
	
	if (arg(ac, av, &x, &y, &obstacle) == EXIT_FAILURE)
		return EXIT_FAILURE;

	void			*dl_handle;
	void			*audio_dl_handle;
	struct timeval	stop, start;
	eDir			direction[4] = {eDir::Left, eDir::Left, eDir::Up, eDir::Space};
	int				accTime = 10;
	int				mode = get_mode(modeTab, 2);
	int				libIndex = get_mode(libNameTab, 3);
	IAudioLib		*audio_library;
	IGraphicLib		*library;

	try {
		audio_library = getAudioLib(&audio_dl_handle);
		library = getLib(&dl_handle, x, y, libTab[libIndex]);
	} catch (std::runtime_error & e) {
		std::cout << "Runtime Error: " << e.what() << std::endl;
		std::exit(1);
	}
	GameCore & 		core = GameCore::getGame(x, y, obstacle, mode);
	library->render( core.getData() );
	while (1)
	{
		gettimeofday(&start, NULL);

		library->getEvent(direction);

		if (direction[2] == eDir::Exit)
		{
			deleteLib(library, dl_handle);
			deleteAudioLib(audio_library, audio_dl_handle);
			break ;
		}
		else if (direction[2] >= eDir::Lib1 && direction[2] <= eDir::Lib3)
		{
			try {
				deleteLib(library, dl_handle);
				library = getLib(& dl_handle, x, y, libTab[direction[2] - eDir::Lib1]);
				direction[2] = eDir::Up;
				library->render( core.getData() );
			} catch (std::runtime_error & e) {
				std::cout << "Runtime Error: " << e.what() << std::endl;
				break;
			}
		}

		if (direction[3] != eDir::Space)
		{
			if (!(core.moveSnake(direction, * audio_library)))
			{
				try {
					deleteLib(library, dl_handle);
					deleteAudioLib(audio_library, audio_dl_handle);
				} catch (std::runtime_error & e) {
					std::cout << "Runtime Error: " << e.what() << std::endl;
				}
				std::cout << "Score: " << core.getData()._score << "\nDEAD\n";
				break;
			}
			core.handle_custom(& custom);
			custom++;
			core.getData()._score += 5;
			library->render( core.getData() );
		}
		gettimeofday(&stop, NULL);
		if (((start.tv_usec > stop.tv_usec) ? 1000000 - start.tv_usec + stop.tv_usec : stop.tv_usec - start.tv_usec) < ( 100000 - accTime))
			usleep((100000 - accTime) - ((start.tv_usec > stop.tv_usec) ? 1000000 - start.tv_usec + stop.tv_usec : stop.tv_usec - start.tv_usec));
		if (accTime + 100 < 50000)
			accTime = core.getData()._score / 5;
	}
	return (0);
}
