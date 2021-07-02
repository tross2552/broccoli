#include "brclpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace brcl
{

	Texture2D* Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    BRCL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLTexture2D(path);
		}

		BRCL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	
}
