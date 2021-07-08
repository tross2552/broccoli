#include "brclpch.h"
#include "RenderContext.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace brcl
{

	std::unique_ptr<RenderContext> RenderContext::Create(void* window) //todo: better window abstraction
	{
		switch (renderer::GetAPI())
		{
		case RendererAPI::API::None:    BRCL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		BRCL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
