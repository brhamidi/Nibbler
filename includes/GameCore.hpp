/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCore.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:21:35 by msrun             #+#    #+#             */
/*   Updated: 2018/05/15 19:30:01 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMECORE_HPP
# define GAMECORE_HPP

#include <list>
#include <array>

class GameCore
{
	public:
		virtual	~GameCore(void);
		static GameCore const &	getGame(void);

	private:
		GameCore(void);
		GameCore(short, short);
		void	_popFood(void);
		void	_buildTheWall(void);

		long long	_score;
		short		_width;
		short		_height;
		std::list< std::pair< short, short > > _snake;
		std::list< std::pair< short, short > > _food;
		std::list< std::pair< short, short > > _obstacle;

		std::array< std::array< char > > _map;
};

#endif
