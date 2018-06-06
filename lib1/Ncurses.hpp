/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ncurses.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:50:07 by msrun             #+#    #+#             */
/*   Updated: 2018/05/31 17:52:00 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSES_HPP
# define NCURSES_HPP

# include <ncurses.h>
# include "IGraphicLib.hpp"
# include <map>
class Ncurses : public IGraphicLib
{
	public:
		Ncurses(short, short);
		~Ncurses(void);

		void	render(Data const &);
		void	getEvent(eDir *direction);

	private:
		void	_init(short, short);
		void	_stop(void);
	//	std::map < int, eDir > _keyFunction;
};

extern "C"
{
	IGraphicLib	*createGraphicLib(short, short);
	void		deleteGraphicLib(IGraphicLib *);
}

#endif
