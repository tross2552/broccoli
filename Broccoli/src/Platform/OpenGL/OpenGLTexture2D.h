#pragma once
#include "Broccoli/Renderer/Texture.h"
#include <glad/glad.h>

namespace brcl
{
	class OpenGLTexture2D : public Texture2D
	{
	public:

		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();
		
		uint32_t GetWidth() const override { return m_Width; };
		uint32_t GetHeight() const override { return m_Height; };
		
		void Bind(uint32_t slot) const override;

		void SetData(void* data, uint32_t size) override;
	private:

		//TODO: asset manager, then remove this
		std::string m_Path;
		
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_Format, m_InternalFormat;
		
	};
	
}
