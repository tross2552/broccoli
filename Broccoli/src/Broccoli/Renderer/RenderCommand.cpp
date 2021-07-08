#include "brclpch.h"
#include "RenderCommand.h"
#include <memory>
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace brcl
{

	std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI = std::make_unique<OpenGLRendererAPI>();
	
}
