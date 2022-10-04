#ifndef _AUDIO_SYS_H
#define _AUDIO_SYS_H

#include <string>
#include <map>

namespace FMOD
{
	class System;
	class Sound;
}

namespace en
{
	class AudioChannel;

	class AudioSys
	{
	public:
		AudioSys() = default;
		~AudioSys() = default;

		void Init();
		void Shutdown();

		void Update();

		void newAudio(const std::string& name, const std::string& filename);

		AudioChannel playAudio(const std::string& name, float volume = 1, float pitch = 1, bool loop = false);
		void stopAudio(const std::string& name);

	private:
		FMOD::System* _fmod_system = nullptr;
		std::map<std::string, FMOD::Sound*> _sounds;

	};
}

#endif // _AUDIO_SYS_H