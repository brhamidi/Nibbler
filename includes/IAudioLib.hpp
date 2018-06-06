/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IAudioLib.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:43:05 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/31 18:56:44 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IAUDIOLIB_HPP
# define IAUDIOLIB_HPP

# include "Nibbler.hpp"

class 	IAudioLib
{
	public:
		virtual void	play(void) = 0;

		virtual ~IAudioLib(void) {}
};

#endif
