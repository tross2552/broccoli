#include "brclpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace brcl
{

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
	
}
