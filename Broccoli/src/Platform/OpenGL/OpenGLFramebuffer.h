#pragma once
#include "Broccoli/Renderer/Framebuffer.h"
#include "glad/glad.h"

namespace brcl
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		
		OpenGLFramebuffer(const FrameBufferSpec& spec);
		~OpenGLFramebuffer() override;

		void Bind() const override;
		void Unbind() const override;

		const FrameBufferSpec& GetSpecification() const { return m_Spec; }
		uint32_t GetWidth() override { return m_Spec.Width; }
		uint32_t GetHeight() override { return m_Spec.Height; }
		void Invalidate() override;

		uint32_t GetColorAttachmentID() const override { return m_ColorAttachment; }
	private:

		uint32_t m_RendererID;
		FrameBufferSpec m_Spec;
		uint32_t m_ColorAttachment, m_DepthAttachment;
	};
}

