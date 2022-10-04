#include "AudioComponent.h"
#include "Engine.h"

namespace en
{
	AudioComponent::~AudioComponent()
	{
		Stop();
	}

	void AudioComponent::Init()
	{
		if (_playOnWake)
		{
			Play();
		}
	}

	void AudioComponent::Update()
	{
			// TODO
	}

	void AudioComponent::Play()
	{
		Stop();
		if (_sound != "") __audiosys.playAudio(_sound, _volume, _pitch, _loop);
	}

	void AudioComponent::Stop()
	{
		_channel.Stop();
	}

	bool AudioComponent::Write(const rapidjson::Value& value) const
	{
		// TODO

		return true;
	}

	bool AudioComponent::Read(const rapidjson::Value& value)
	{
		std::string& sound_name = _sound;
		float& volume = _volume;
		float& pitch = _pitch;
		bool& play_on_start = _playOnWake;
		bool& loop = _loop;

		READ_DATA(value, sound_name);
		READ_DATA(value, volume);
		READ_DATA(value, pitch);
		READ_DATA(value, play_on_start);
		READ_DATA(value, loop);

		__audiosys.newAudio(sound_name, sound_name);

		return true;
	}
}