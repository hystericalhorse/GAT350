#ifndef _COMPONENT_AUDIO_H
#define _COMPONENT_AUDIO_H

#include "Framework/Component.h"
#include "Audio/AudioChannel.h"
#include <string>

namespace en
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;
		~AudioComponent();

		CLONE(AudioComponent)

		void Init() override;
		void Update() override;
		void Play();
		void Stop();

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		AudioChannel _channel;

		std::string _sound;
		bool _playOnWake = false;
		bool _loop = false;
		float _volume = 0.5f;
		float _pitch = 0.5f;

	};
}

#endif _COMPONENT_AUDIO_H
