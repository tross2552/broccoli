#pragma once

#include "Broccoli/Math/Math.h"

namespace brcl
{
	//TODO: abstract implementation away from GL
	class Shader
	{
		
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& uniformName, const Matrix4x4& matrix);
	
	private:
		uint32_t m_RendererID;
	};
}
