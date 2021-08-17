#pragma once
#include <xaudio2.h>

#include "Broccoli/Audio/AudioDevice.h"

namespace brcl
{
	class XAudio2Device : public AudioDevice
	{
	public:

		XAudio2Device() = default;
		
		void Init() override;
		void Play() override;
		void Pause() override;
		void Stop() override;

		static IXAudio2* GetEngine() { return s_pXAudio2.get(); }

		
	
	private:
		static std::shared_ptr<IXAudio2> s_pXAudio2;
		std::shared_ptr<IXAudio2MasteringVoice> m_pMasterVoice;
	};

}
