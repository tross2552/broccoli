#pragma once

namespace brcl
{
	enum class AudioFormat
	{
		WAVE,
		OGG
	};
	
	class AudioClip
	{
	public:
		AudioClip(AudioFormat format, unsigned channels, unsigned sampleRate)
			: m_Format(format), m_Channels(channels), m_SampleRate(sampleRate)
		{
		}

		AudioFormat GetFormat() { return m_Format; }
		unsigned int GetChannels() { return m_Channels; }
		unsigned int GetSampleRate() { return m_SampleRate; }

		static std::unique_ptr<AudioClip> Create(std::string path);
		
	private:

		AudioFormat m_Format;
		unsigned int m_Channels;
		unsigned int m_SampleRate;
		
	};
	
}