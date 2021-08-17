#pragma once
#include "AudioDevice.h"

namespace brcl
{
	class AudioSource
	{
	public:
		virtual ~AudioSource() = default;

		virtual void LoadClip(std::string path) = 0;

		virtual void Start() = 0;
		virtual void Stop() = 0;

		static std::unique_ptr<AudioSource> Create();

	};
}