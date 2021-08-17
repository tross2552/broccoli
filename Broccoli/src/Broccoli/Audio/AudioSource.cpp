#include "brclpch.h"
#include "AudioSource.h"

#include "Platform/XAudio2/XAudio2Source.h"

namespace brcl
{
	std::unique_ptr<AudioSource> AudioSource::Create()
	{
		switch (AudioDevice::GetAPI())
		{
		case AudioDevice::API::None:    BRCL_CORE_ASSERT(false, "AudioAPI::None is currently not supported!"); return nullptr;
		case AudioDevice::API::XAudio2:  return std::make_unique <XAudio2Source>();
		}

		BRCL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
