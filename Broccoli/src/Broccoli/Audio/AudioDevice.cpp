#include "brclpch.h"
#include "AudioDevice.h"

#include "Platform/XAudio2/XAudio2Device.h"

namespace brcl
{
	AudioDevice::API AudioDevice::s_API = API::XAudio2;


	std::unique_ptr<AudioDevice> AudioDevice::Create()
	{
		return std::make_unique<XAudio2Device>();
	}
}
