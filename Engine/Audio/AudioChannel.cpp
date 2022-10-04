#include "AudioChannel.h"
#include <fmod.hpp>

namespace en
{
	bool AudioChannel::isPlaying()
	{
		if (!_channel) return false;

		bool isPlaying;
		_channel->isPlaying(&isPlaying);

		return isPlaying;
	}

	void AudioChannel::Stop()
	{
		if (isPlaying()) _channel->stop();
	}

	void AudioChannel::setPitch(const float& pitch)
	{
		if (isPlaying()) _channel->setPitch(pitch);
	}

	float& AudioChannel::getPitch()
	{
		float pitch = 0.0;
		if (isPlaying()) _channel->getPitch(&pitch);

		return pitch;
	}

	void AudioChannel::setVolume(const float& volume)
	{
		if (isPlaying()) _channel->setVolume(volume);
	}

	float& AudioChannel::getVolume()
	{
		float volume = 0.0;
		if (isPlaying()) _channel->getVolume(&volume);

		return volume;
	}
}