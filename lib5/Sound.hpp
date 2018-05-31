/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sound.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:40:16 by bhamidi           #+#    #+#             */
/*   Updated: 2018/05/31 18:54:23 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_HPP
# define SOUND_HPP

#include "IAudioLib.hpp"
#include <SFML/Audio.hpp>

class Sound : public IAudioLib
{
	private:
		sf::SoundBuffer	_buffer;
		sf::Sound		_sound;

	public:
		Sound(void);
		~Sound(void);

		void play(void);
};

extern "C"
{
	Sound	*createAudioLib(void);
	void	deleteAudioLib(Sound *);
}

#endif
