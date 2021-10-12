#include "brclpch.h"
#include "XAudio2Clip.h"

#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'

namespace brcl
{

	XAudio2Clip::XAudio2Clip(std::string path) :
		AudioClip(AudioFormat::WAVE, 2, 41100), m_Path(path)
	{

		const char* cPath = path.c_str();
		size_t newsize = strlen(cPath) + 1;

		// Convert char* string to a wchar_t* string.
		wchar_t* wcPath = new wchar_t[newsize];
		size_t convertedChars = 0;
		mbstowcs_s(&convertedChars, wcPath, newsize, path.c_str(), _TRUNCATE);
		
		HRESULT hr = S_OK;

		// Open the file
		HANDLE hFile = CreateFile(
			wcPath,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
			BRCL_CORE_ASSERT(0, "XAudio2 Error: Invalid file handle");


		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, nullptr, FILE_BEGIN))
			BRCL_CORE_ASSERT(0, "XAudio2 Error: Invalid file pointer");
			


		DWORD dwChunkSize;
		DWORD dwChunkPosition;
		//check the file type, should be fourccWAVE or 'XWMA'
		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
		DWORD filetype;
		ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if (filetype != fourccWAVE)
			BRCL_CORE_ASSERT(0,"XAudio2 Error: Invalid file format {0}", filetype);

		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &m_Data.wfx, dwChunkSize, dwChunkPosition);


		//fill out the audio data buffer with the contents of the fourccDATA chunk
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		BYTE* pDataBuffer = new BYTE[dwChunkSize];
		ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);


		m_Data.buffer.AudioBytes = dwChunkSize; //size of the audio buffer in bytes
		m_Data.buffer.pAudioData = pDataBuffer; //buffer containing audio data
		m_Data.buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
	}

	void XAudio2Clip::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
	{
		HRESULT hr = S_OK;
		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
			BRCL_CORE_ASSERT(0,"XAudio2 File Error: Invalid file pointer");

		DWORD dwChunkType;
		DWORD dwChunkDataSize;
		DWORD dwRIFFDataSize = 0;
		DWORD dwFileType;
		DWORD bytesRead = 0;
		DWORD dwOffset = 0;

		while (hr == S_OK)
		{
			DWORD dwRead;
			if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
				BRCL_CORE_ASSERT(0,"XAudio2 File Error: Read error");

			if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
				BRCL_CORE_ASSERT(0, "XAudio2 File Error: Read error");

			switch (dwChunkType)
			{
			case fourccRIFF:
				dwRIFFDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;
				if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
					BRCL_CORE_ASSERT(0, "XAudio2 File Error: Read error");
				break;

			default:
				if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
					BRCL_CORE_ASSERT(0, "XAudio2 File Error: Read error");
			}

			dwOffset += sizeof(DWORD) * 2;

			if (dwChunkType == fourcc)
			{
				dwChunkSize = dwChunkDataSize;
				dwChunkDataPosition = dwOffset;
				return;
			}

			dwOffset += dwChunkDataSize;

			if (bytesRead >= dwRIFFDataSize)
				BRCL_CORE_ASSERT(0, "XAudio2 File Error: Read error");

		}
	}

	void XAudio2Clip::ReadChunkData(HANDLE hFile, void* buffer, DWORD bufferSize, DWORD bufferOffset)
	{
		HRESULT hr = S_OK;
		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferOffset, NULL, FILE_BEGIN))
		{
			BRCL_CORE_ASSERT(0,"XAudio2 File Error: Invalid file pointer");
			return;
		}
		DWORD dwRead;
		if (0 == ReadFile(hFile, buffer, bufferSize, &dwRead, NULL))
			BRCL_CORE_ASSERT(0, "XAudio2 File Error: Read error");
	}
	
}