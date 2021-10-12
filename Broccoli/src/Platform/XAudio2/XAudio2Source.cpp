#include "brclpch.h"
#include "XAudio2Source.h"

namespace brcl
{
	void XAudio2Source::Start()
	{
		HRESULT hr = S_OK;

		IXAudio2SourceVoice* pSourceVoice;
		hr = XAudio2Device::GetEngine()->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&m_Clip->GetData().wfx);
		BRCL_CORE_ASSERT(!FAILED(hr), "XAudio2 Error: Failed to play file");

		hr = pSourceVoice->SubmitSourceBuffer(&m_Clip->GetData().buffer);
		BRCL_CORE_ASSERT(!FAILED(hr), "XAudio2 Error: Failed to play file");

		hr = pSourceVoice->Start(0);
		BRCL_CORE_ASSERT(!FAILED(hr), "XAudio2 Error: Failed to play file");
	}

	void XAudio2Source::Stop()
	{
		//todo: implement
	}

	void XAudio2Source::LoadClip(std::string path)
	{
		m_Clip = new XAudio2Clip(path);
	}
}
