/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IGraphicLib.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:28:58 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/21 15:03:52 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IGRAPHICLIB_HPP
# define IGRAPHICLIB_HPP

# include "Nibbler.hpp"

class 	IGraphicLib
{
	private:
		virtual void	_init(void) = 0;
		virtual void	_stop(void) = 0;

	public:
		virtual void	render(Data const &) const = 0;
		virtual eDir	getEvent(void) const = 0;

		virtual ~IGraphicLib(void) {}
};

#endif
