#pragma once

namespace brcl
{

	class Shader
	{
		
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

		//TODO: decide how to handle uniforms
		//void UploadUniformFloat4(const std::string& uniformName, const Vector4& vector);
		//void UploadUniformMat4(const std::string& uniformName, const Matrix4x4& matrix);
		
	};
}
