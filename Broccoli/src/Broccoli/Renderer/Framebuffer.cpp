#include "brclpch.h"
#include "Framebuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace brcl
{
	std::unique_ptr<Framebuffer> Framebuffer::Create(const FrameBufferSpec& spec)
	{
		switch (renderer::GetAPI())
		{
		case RendererAPI::API::None:    BRCL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLFramebuffer>(spec);
		}

		BRCL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
