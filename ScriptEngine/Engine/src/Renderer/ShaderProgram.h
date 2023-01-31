#pragma once

#include "../ExportPropety.h"

#include <glm/mat4x4.hpp>

#include <string>

typedef unsigned int GLuint;
typedef unsigned int GLenum;
typedef int GLint;

class DLLEXPORT ShaderProgram
{
public:
	ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	~ShaderProgram();

	ShaderProgram() = delete;
	ShaderProgram(ShaderProgram&);
	ShaderProgram& operator=(const ShaderProgram&) = delete;
	ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
	ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

	bool isCompiled() const;
	void use() const;
	void setInt(const std::string& name, const GLint value);
	void setMatrix4(const std::string& name, const glm::mat4& matrix);
private:
	bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
	bool m_isCompiled = false;
	GLuint m_ID = 0;
};