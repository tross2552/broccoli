#pragma once
#include "Broccoli/Math/Math.h"
#include "Broccoli/Renderer/Shader.h"

//todo: REMOVE !!!!!!!!!! 
typedef unsigned int GLenum;

namespace brcl
{
	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader() override;

		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> Preprocess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& sources);

		const std::string& GetName() const override { return m_Name; }

		void Bind() const override;
		void Unbind() const override;

		void SetUniformInt    (const std::string& uniformName, int value)               override { UploadUniformInt    ( uniformName,  value ); }
		void SetUniformFloat  (const std::string& uniformName, float value)             override { UploadUniformFloat  ( uniformName,  value ); }
		void SetUniformFloat2 (const std::string& uniformName, const Vector2& vector)   override { UploadUniformFloat2 ( uniformName, vector ); }
		void SetUniformFloat3 (const std::string& uniformName, const Vector3& vector)   override { UploadUniformFloat3 ( uniformName, vector ); }
		void SetUniformFloat4 (const std::string& uniformName, const Vector4& vector)   override { UploadUniformFloat4 ( uniformName, vector ); }
		void SetUniformMat3   (const std::string& uniformName, const Matrix4x4& matrix) override { UploadUniformMat3   ( uniformName, matrix ); }
		void SetUniformMat4   (const std::string& uniformName, const Matrix4x4& matrix) override { UploadUniformMat4   ( uniformName, matrix ); }

		void UploadUniformInt    (const std::string& uniformName, int value);
		
		void UploadUniformFloat  (const std::string& uniformName, float value);
		void UploadUniformFloat2 (const std::string& uniformName, const Vector2& vector);
		void UploadUniformFloat3 (const std::string& uniformName, const Vector3& vector);
		void UploadUniformFloat4 (const std::string& uniformName, const Vector4& vector);

		void UploadUniformMat3   (const std::string& uniformName, const Matrix3x3& matrix);
		void UploadUniformMat4   (const std::string& uniformName, const Matrix4x4& matrix);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}
