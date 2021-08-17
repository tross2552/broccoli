#pragma once
#include "Broccoli/Audio/AudioSource.h"
#include "XAudio2Clip.h"
#include "XAudio2Device.h"
#include <xaudio2.h>


namespace brcl
{
	class XAudio2Source : public AudioSource
	{
	public:

		void Start() override;
		void Stop() override;

		void LoadClip(std::string path) override;
	private:
		XAudio2Clip* m_Clip = nullptr;
	};
}

