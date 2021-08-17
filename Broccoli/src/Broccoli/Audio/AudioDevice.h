#pragma once

namespace brcl
{

	class AudioDevice
	{
	public:

		enum class API
		{
			None = 0, XAudio2 = 1
		};

	public:
		virtual ~AudioDevice() = default;
		
		virtual void Init() = 0;
		virtual void Play() = 0;
		virtual void Pause() = 0;
		virtual void Stop() = 0;

		static API GetAPI() { return s_API; }

		static std::unique_ptr<AudioDevice> Create();

	private:
		
		static API s_API;
		static AudioDevice* s_Device;
		
	};
}

