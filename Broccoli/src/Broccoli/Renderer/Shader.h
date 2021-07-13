#pragma once
#include "Broccoli/Math/Math.h"

namespace brcl
{

	class Shader
	{
		
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		static std::unique_ptr<Shader> Create(const std::string& path); //TODO: proper filesystem
		static std::unique_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual void SetUniformInt      (const std::string& uniformName, int   value) = 0;
		virtual void SetUniformIntArray (const std::string& uniformName, int*  values, uint32_t count) = 0;
		virtual void SetUniformFloat    (const std::string& uniformName, float value) = 0;
		virtual void SetUniformFloat2   (const std::string& uniformName, const Vector2&   vector) = 0;
		virtual void SetUniformFloat3   (const std::string& uniformName, const Vector3&   vector) = 0;
		virtual void SetUniformFloat4   (const std::string& uniformName, const Vector4&   vector) = 0;
		virtual void SetUniformMat3     (const std::string& uniformName, const Matrix4x4& matrix) = 0;
		virtual void SetUniformMat4     (const std::string& uniformName, const Matrix4x4& matrix) = 0;
		
	};

	class ShaderLibrary
	{
	public:

		void Add(const std::string& name, std::shared_ptr<Shader> shader);
		void Add(std::shared_ptr<Shader> shader);

		std::shared_ptr<Shader> Load(const std::string& path);
		std::shared_ptr<Shader> Load(const std::string& name, const std::string& path);
		
		std::shared_ptr<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const { return m_Shaders.find(name) != m_Shaders.end(); }

	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}
