#ifndef _AUDIO_CHANNEL_H
#define _AUDIO_CHANNEL_H

namespace FMOD
{
	class Channel;
}

namespace en
{
	class AudioChannel
	{
	public:
		AudioChannel() = default;
		AudioChannel(FMOD::Channel* channel) :
			_channel{channel}
		{}

		bool isPlaying();
		void Stop();

		void setPitch(const float& pitch);
		float& getPitch();

		void setVolume(const float& volume);
		float& getVolume();

	private:
		FMOD::Channel* _channel = nullptr;

	};
}

#endif // _AUDIO_CHANNEL_H