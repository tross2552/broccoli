#pragma once
#include "Broccoli/Math/Math.h"
#include "Broccoli/Renderer/Shader.h"

namespace brcl
{
	class OpenGLShader : public Shader
	{
	public:
		
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		void UploadUniformInt    (const std::string& uniformName, int vector);
		
		void UploadUniformFloat  (const std::string& uniformName, float value);
		void UploadUniformFloat2 (const std::string& uniformName, const Vector2& vector);
		void UploadUniformFloat3 (const std::string& uniformName, const Vector3& vector);
		void UploadUniformFloat4 (const std::string& uniformName, const Vector4& vector);

		void UploadUniformMat3   (const std::string& uniformName, const Matrix3x3& matrix);
		void UploadUniformMat4   (const std::string& uniformName, const Matrix4x4& matrix);

	private:
		uint32_t m_RendererID;
	};

}