#include "ShaderProgram.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "../Helpers/casts.h"
#include "../Logging/Clerk.h"

ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint vertexShaderID;
	if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
	{
#ifdef LOG_ERR
		Clerk::Misstep(13, __FILE__, "ShaderProgram::ShaderProgram", L"VERTEX SHADER compile time error");
#endif
		return;
	}

	GLuint fragmentShaderID;
	if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
	{
#ifdef LOG_ERR
		Clerk::Misstep(24, __FILE__, "ShaderProgram::ShaderProgram", L"FRAGMENT SHADER compile time error");
#endif
		glDeleteShader(vertexShaderID);
		return;
	}

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShaderID);
	glAttachShader(m_ID, fragmentShaderID);
	glLinkProgram(m_ID);

	GLint success;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		GLchar infolog[1024];
		glGetShaderInfoLog(m_ID, 1024, nullptr, infolog);
#ifdef LOG_ERR
		Clerk::Misstep(36, __FILE__, "ShaderProgram::ShaderProgram", Casts::StringToWstring(std::string("ERROR::SHADER: Link time error: ") + std::string(infolog)));
#endif
	}
	else
	{
		m_isCompiled = true;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}
ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ID);
}

bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
{
	shaderID = glCreateShader(shaderType);
	const char* code = source.c_str();
	glShaderSource(shaderID, 1, &code, nullptr);
	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infolog[1024];
		glGetShaderInfoLog(shaderID, 1024, nullptr, infolog);
		Clerk::Misstep(67, __FILE__, "ShaderProgram::ShaderProgram", Casts::StringToWstring(std::string("ERROR::SHADER: Compile time error: ") + std::string(infolog)));
		std::cerr << "ERROR::SHADER: Compile time error:\n" << infolog << std::endl;
		system("pause");
		return false;
	}
	return true;
}

void ShaderProgram::use() const
{
	glUseProgram(m_ID);
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
{
	glDeleteProgram(m_ID);
	m_ID = shaderProgram.m_ID;
	m_isCompiled = shaderProgram.m_isCompiled;

	shaderProgram.m_ID = 0;
	shaderProgram.m_isCompiled = false;

	return *this;
}

ShaderProgram::ShaderProgram(ShaderProgram& shaderProgram)
{
	m_ID = shaderProgram.m_ID;
	m_isCompiled = shaderProgram.m_isCompiled;

	shaderProgram.m_ID = 0;
	shaderProgram.m_isCompiled = false;
}

ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
{
	m_ID = shaderProgram.m_ID;
	m_isCompiled = shaderProgram.m_isCompiled;

	shaderProgram.m_ID = 0;
	shaderProgram.m_isCompiled = false;
}

void ShaderProgram::setInt(const std::string& name, const GLint value)
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix)
{

	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

bool ShaderProgram::isCompiled() const { return m_isCompiled; }

