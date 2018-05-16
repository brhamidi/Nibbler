/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:21:35 by msrun             #+#    #+#             */
/*   Updated: 2018/05/16 18:37:05 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMECORE_HPP
# define GAMECORE_HPP

#include <list>
#include <iostream>

struct Data
{
	long long								_score;
	short									_width;
	short									_height;
	short ** 								_map;

};

class GameCore
{
	public:
		~GameCore(void);
		static GameCore const &	getGame(short, short);

	private:
		GameCore(short, short);
		GameCore(void);
		void	_buildTheWall(void);
		void	_popFood(void);
		void	_printMap(void);

		std::list< std::pair< short, short > >	_snake;
		std::list< std::pair< short, short > >	_food;
		Data	_data;
};

#endif
