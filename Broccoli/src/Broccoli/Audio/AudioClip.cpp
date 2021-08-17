#include "brclpch.h"
#include "AudioClip.h"

#include "AudioDevice.h"
#include "Platform/XAudio2/XAudio2Clip.h"

namespace brcl
{
	std::unique_ptr<AudioClip> AudioClip::Create(std::string path)
	{
		switch (AudioDevice::GetAPI())
		{
		case AudioDevice::API::None:    BRCL_CORE_ASSERT(false, "AudioAPI::None is currently not supported!"); return nullptr;
		case AudioDevice::API::XAudio2:  return std::make_unique <XAudio2Clip>(path);
		}

		BRCL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}