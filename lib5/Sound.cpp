/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sound.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:40:21 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/31 18:57:14 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sound.hpp"

Sound::Sound(void)
{
	this->_buffer.loadFromFile("lib5/sound.wav");
	this->_sound.setBuffer(this->_buffer);
}
Sound::~Sound(void)
{
}

void 	Sound::play(void)
{
	this->_sound.play();
}

Sound	*createAudioLib(void)
{
	return new Sound();
}

void	deleteAudioLib(Sound *audioLib)
{
	delete audioLib;
}
