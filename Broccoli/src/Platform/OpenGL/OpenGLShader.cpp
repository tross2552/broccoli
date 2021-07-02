#include "brclpch.h"
#include "OpenGLShader.h"
#include "glad/glad.h"

namespace brcl
{
	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{

		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			BRCL_CORE_ERROR("Vertex shader compilation failure!");
			BRCL_CORE_ERROR("{0}", infoLog.data());

			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			BRCL_CORE_ERROR("Fragment shader compilation failure!");
			BRCL_CORE_ERROR("{0}", infoLog.data());

			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			BRCL_CORE_ERROR("Shader link failure!");
			BRCL_CORE_ERROR("{0}", infoLog.data());

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
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
				matrixCopy[i * 4 + j] = matrix(i, j);
		}

		glUniformMatrix4fv(location, 1, GL_FALSE, matrixCopy);
	}
}
