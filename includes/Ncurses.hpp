/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ncurses.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:50:07 by msrun             #+#    #+#             */
/*   Updated: 2018/05/18 14:11:39 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSESGRAPH_HPP
# define NCURSESGRAPH_HPP

# include <ncurses.h>
# include "GameCore.hpp"

class Ncurses
{
	public:
		Ncurses(void);
		~Ncurses(void);
		Ncurses(Ncurses const &);
		Ncurses &	operator=(Ncurses const &);
		int	printMap(Data &);

	private:

};

#endif
