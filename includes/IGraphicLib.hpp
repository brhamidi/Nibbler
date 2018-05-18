/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IGraphicLib.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:28:58 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/18 17:21:56 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IGRAPHICLIB_HPP
# define IGRAPHICLIB_HPP

# include "GameCore.hpp"

class 	IGraphicLib
{
	private:
		void	init(void) = 0;
		void	stop(void) = 0;

	public:
		void	render(Data & const) const = 0;
		eDir	getEvent(void) const = 0;

		virtual ~IGraphicLib(void) {}
};

#endif
