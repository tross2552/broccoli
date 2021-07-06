#include "brclpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace brcl
{
	Shader* Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    BRCL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(path);
		}

		BRCL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	
	Shader* Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    BRCL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(name, vertexSrc, fragmentSrc);
		}

		BRCL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, std::shared_ptr<Shader> shader)
	{
		BRCL_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader library error: shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(std::shared_ptr<Shader> shader)
	{
		const std::string& name = shader->GetName();
		Add(name, shader);
	}
	

	Shader* ShaderLibrary::Load(const std::string& path)
	{
		auto shader = Shader::Create(path);
		if (!shader) return nullptr;
		
		Add(std::shared_ptr<Shader>(shader));
		return shader;
		
	}

	Shader* ShaderLibrary::Load(const std::string& name, const std::string& path)
	{
		auto shader = Shader::Create(path);
		if (!shader) return nullptr;
		
		Add(std::shared_ptr<Shader>(shader));
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
	{
		BRCL_CORE_ASSERT(Exists(name), "Shader library error: shader doesn't exist!");
		return m_Shaders[name];
	}
}
