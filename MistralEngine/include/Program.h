#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class Program
{
public:
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
	Program() {};

	Program(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr) {
		load(vertexPath, fragmentPath, geometryPath);
	}

	~Program() { glDeleteProgram(id); };

	// build shader
	// ------------------------------------------------------------------------
	void load(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr, const char* tessellationControlPath = nullptr,
		const char* tessellationEvaluationPath = nullptr);

	void checkCompileErrors(GLuint shader, std::string type);

	GLint getId() { return id; }

	GLint setId(GLint newId) { id = newId; }


	void use()
	{
		glUseProgram(id);
	}

	void setBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value)
	{
		glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string& name, float x, float y)
	{
		glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat)
	{
		glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat)
	{
		glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat)
	{
		glProgramUniformMatrix4fv(id, glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);

	}

private:
	GLint id = NULL;
};
#endif