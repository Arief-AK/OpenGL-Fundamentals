#pragma once

// INCLUDES
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	
	// Member variables
	unsigned int m_id;

	// Default constructor
	Shader();

	// Overloaded
	Shader(const char* vertexPath, const char* fragmentPath);
	
	// Destructor
	~Shader();

	// Activate the shader
	void activate();

	// Uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	// Uniform vector functions
	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;

	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;

	// Uniform matrix functions
	void setMat2(const std::string& name, const glm::mat2& value) const;
	void setMat3(const std::string& name, const glm::mat3& value) const;
	void setMat4(const std::string& name, const glm::mat4& value) const;

private:

	// Member variables
	unsigned int m_vertex_shader;
	unsigned int m_fragment_shader;
	unsigned int m_vbo, m_vao;

	// Member functions
	void InitialiseShaders(unsigned int* vertexShader, unsigned int* fragmentShader, const char* vertexShaderSource, const char* fragmentShaderSource);
	void InitialiseShaderProgram(unsigned int* vertexShader, unsigned int* fragmentShader, unsigned int* shaderProgram);
};
