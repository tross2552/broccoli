#include "brclpch.h"
#include "OpenGLShader.h"
#include "glad/glad.h"

#include <fstream>
#include <filesystem>

namespace brcl
{

	static GLenum ShaderTypeFromString(const std::string& shaderType) //todo: proper string handling
	{
		if (shaderType == "Vertex")   return GL_VERTEX_SHADER;
		if (shaderType == "vertex")   return GL_VERTEX_SHADER;
		if (shaderType == "Fragment") return GL_FRAGMENT_SHADER;
		if (shaderType == "fragment") return GL_FRAGMENT_SHADER;

		BRCL_CORE_ASSERT(false, "OpenGl Shader error: unknown shader type!");
	}
	
	OpenGLShader::OpenGLShader(const std::string& path)
	{
		std::filesystem::path filepath = path;
		m_Name = filepath.stem().string();
		
		std::string shaderSource = ReadFile(path);
		auto shaderSources = Preprocess(shaderSource);
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		m_Name = name;
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER]   = vertexSource;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSource;

		Compile(shaderSources);
		
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		std::ifstream shaderIn(path, std::ios::in | std::ios::binary);

		if (!shaderIn) BRCL_CORE_ERROR("OpenGl Shader error: Failed to load file '{0}'", path);

		std::string result;
		shaderIn.seekg(0, std::ios::end);
		result.resize(shaderIn.tellg());
		shaderIn.seekg(0, std::ios::beg);
		shaderIn.read(&result[0], result.size());
		shaderIn.close();

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while(pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			BRCL_CORE_ASSERT(eol != std::string::npos, "OpenGl Shader error: syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& sources)
	{

		GLuint program = glCreateProgram();
		BRCL_CORE_ASSERT(sources.size() <= 8, "OpenGL Shader Error: OpenGL programs can only be compiled with up to 8 shaders.");
		std::array<GLenum, 8> glShaderIds;

		int shaderIndex = 0;
		
		for(auto& kv : sources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;
			
			GLuint shader = glCreateShader(type);
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);
			
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
				
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				
				glDeleteShader(shader);
				for (auto shaderID : glShaderIds) glDeleteShader(shaderID);
				
				BRCL_CORE_ERROR("OpenGL Shader: compilation failure!");
				BRCL_CORE_ERROR("{0}", infoLog.data());
				
				break;
			}

			glAttachShader(program, shader);
			glShaderIds[shaderIndex] = shader;

			shaderIndex++;
		}

		m_RendererID = program;
		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);
			
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);
			
			glDeleteProgram(m_RendererID);
			for (auto shaderID : glShaderIds) glDeleteShader(shaderID);
			
			BRCL_CORE_ERROR("OpenGl Shader link failure!");
			BRCL_CORE_ERROR("{0}", infoLog.data());
			
			return;
		}

		for (auto shaderID : glShaderIds) glDetachShader(m_RendererID, shaderID);
		
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& uniformName, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& uniformName, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& uniformName, const Vector2& vector)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform2f(location, vector[0], vector[1]);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& uniformName, const Vector3& vector)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform3f(location, vector[0], vector[1], vector[2]);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& uniformName, const Vector4& vector)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform4f(location, vector[0], vector[1], vector[2], vector[3]);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& uniformName, const Matrix3x3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());

		static float* matrixCopy = new float[9];
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				matrixCopy[i * 3 + j] = matrix(i, j);
		}

		glUniformMatrix3fv(location, 1, GL_FALSE, matrixCopy);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& uniformName, const Matrix4x4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());

		static float* matrixCopy = new float[16];
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				matrixCopy[i + j * 4] = matrix(i, j);
		}

		glUniformMatrix4fv(location, 1, GL_FALSE, matrixCopy);
	}
}
