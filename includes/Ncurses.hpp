/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ncurses.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:50:07 by msrun             #+#    #+#             */
/*   Updated: 2018/05/18 18:01:00 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSES_HPP
# define NCURSES_HPP

# include <ncurses.h>
# include "GameCore.hpp"
# include "IGraphicLib.hpp"

class Ncurses : public IGraphicLib
{
	public:
		Ncurses(void);
		~Ncurses(void);

		void	render(Data const &) const;
		eDir	getEvent(void) const;

	private:
		void	_init(void);
		void	_stop(void);

};

#endif
