#include "brclpch.h"
#include "XAudio2Device.h"

namespace brcl
{

	std::shared_ptr<IXAudio2> XAudio2Device::s_pXAudio2(nullptr);
	
	void XAudio2Device::Init()
	{

		HRESULT hr;

		IXAudio2* pXAudio2 = nullptr;
		IXAudio2MasteringVoice* pMasterVoice = nullptr;
		
		hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		if (FAILED(hr))
		{
			BRCL_CORE_ERROR("XAudio2 Error: Failed to initialize COM");
			return;
		}
			

		hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
		if (FAILED(hr))
		{
			BRCL_CORE_ERROR("XAudio2 Error: Failed to initialize engine");
			return;
		}
			

		hr = pXAudio2->CreateMasteringVoice(&pMasterVoice);
		if (FAILED(hr))
		{
			BRCL_CORE_ERROR("XAudio2 Error: Failed to create mastering voice");
			return;
		}

		s_pXAudio2.reset(pXAudio2);
		m_pMasterVoice.reset(pMasterVoice);
	}

	void XAudio2Device::Play()
	{
	}

	void XAudio2Device::Pause()
	{
	}

	void XAudio2Device::Stop()
	{
	}
}
