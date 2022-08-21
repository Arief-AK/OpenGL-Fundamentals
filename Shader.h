#pragma once

// INCLUDES
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	
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
	void setFoat(const std::string& name, float value) const;

private:

	// Member variables
	unsigned int m_id;
	unsigned int m_vertex_shader;
	unsigned int m_fragment_shader;
	unsigned int m_vbo, m_vao;

	// Member functions
	void InitialiseShaders(unsigned int* vertexShader, unsigned int* fragmentShader, const char* vertexShaderSource, const char* fragmentShaderSource);
	void InitialiseShaderProgram(unsigned int* vertexShader, unsigned int* fragmentShader, unsigned int* shaderProgram);
};
