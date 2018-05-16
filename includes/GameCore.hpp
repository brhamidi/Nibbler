/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:21:35 by msrun             #+#    #+#             */
/*   Updated: 2018/05/16 17:10:18 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMECORE_HPP
# define GAMECORE_HPP

#include <list>
#include <iostream>

class GameCore
{
	public:
		~GameCore(void);
		static GameCore const &	getGame(short, short);

	private:
		GameCore(short, short);
		GameCore(void);
		void	_buildTheWall(void);
		void	_printMap(void);

		long long								_score;
		const short								_width;
		const short								_height;
		std::list< std::pair< short, short > >	_snake;
		std::list< std::pair< short, short > >	_food;
		std::list< std::pair< short, short > >	_obstacle;
		short ** 								_map;
};

#endif
