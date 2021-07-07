#pragma once

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

		//TODO: decide how to handle uniforms
		//void UploadUniformFloat4(const std::string& uniformName, const Vector4& vector);
		//void UploadUniformMat4(const std::string& uniformName, const Matrix4x4& matrix);
		
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
