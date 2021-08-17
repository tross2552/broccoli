#pragma once
#include <xaudio2.h>

#include "Broccoli/Audio/AudioClip.h"

namespace brcl
{

	struct XAudio2SampleData
	{
		XAUDIO2_BUFFER buffer = { 0 };
		WAVEFORMATEXTENSIBLE wfx = { 0 };
	};
	
	class XAudio2Clip : public AudioClip
	{
	public:
		
		XAudio2Clip(std::string path);

		XAudio2SampleData& GetData() { return m_Data; }
	
	private:
		
		void FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
		void ReadChunkData(HANDLE hFile, void* buffer, DWORD bufferSize, DWORD bufferOffset);
	
	private:
		//TODO: asset manager, then remove this
		std::string m_Path;
		
		XAudio2SampleData m_Data;
		
	};
}
