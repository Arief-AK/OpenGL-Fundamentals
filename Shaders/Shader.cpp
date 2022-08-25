
// INCLUDES
#include "Shader.h"

Shader::Shader()
{
	m_id = glCreateProgram();
    m_vao = 0, m_vbo = 0, m_vertex_shader = 0, m_fragment_shader = 0;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertex_code;
    std::string fragment_code;

    std::ifstream vertex_shader_file;
    std::ifstream fragment_shader_file;

    // Ensure streams can throw exceptions
    vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    // Attempt to open and parse the source files
    try
    {
        // Open the files
        vertex_shader_file.open(vertexPath);
        fragment_shader_file.open(fragmentPath);

        // Create streams for parsing strings
        std::stringstream vertex_shader_stream;
        std::stringstream fragment_shader_stream;

        // Attempt to read the content of buffer in the file into the streams
        vertex_shader_stream << vertex_shader_file.rdbuf();
        fragment_shader_stream << fragment_shader_file.rdbuf();

        // Close the files
        vertex_shader_file.close();
        fragment_shader_file.close();

        // Convert the streams into strings
        vertex_code = vertex_shader_stream.str();
        fragment_code = fragment_shader_stream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    // Convert code strings into literal strings
    const char* vertexSource = vertex_code.c_str();
    const char* fragmentSource = fragment_code.c_str();

    // Initialise the shaders
    InitialiseShaders(&m_vertex_shader, &m_fragment_shader, vertexSource, fragmentSource);

    // Initialise the shader program
    InitialiseShaderProgram(&m_vertex_shader, &m_fragment_shader, &m_id);
}

Shader::~Shader()
{
    // Perform cleanup of shaders
    glDeleteShader(m_vertex_shader);
    glDeleteShader(m_fragment_shader);
    glDeleteProgram(m_id);
}

void Shader::activate()
{
    glUseProgram(m_id);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::InitialiseShaders(unsigned int* vertexShader, unsigned int* fragmentShader, const char* vertexShaderSource, const char* fragmentShaderSource)
{
    // ********************* VERTEX SHADER *********************

    // Create and compile vertex shader
    *vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(*vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(*vertexShader);

    // Check for compilation error
    int successful_vertex_compilation;
    glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &successful_vertex_compilation);

    if (!successful_vertex_compilation)
    {
        char infoLog[512];
        glGetShaderInfoLog(*vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ********************* FRAGMENT SHADER *********************

    // Create and compile fragment shader
    *fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(*fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(*fragmentShader);

    // Check for compilation error
    int successful_fragment_compilation;
    glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &successful_fragment_compilation);

    if (!successful_fragment_compilation)
    {
        char infoLog[512];
        glGetShaderInfoLog(*fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::InitialiseShaderProgram(unsigned int* vertexShader, unsigned int* fragmentShader, unsigned int* shaderProgram)
{
    // ********************* SHADER PROGRAM *********************
    *shaderProgram = glCreateProgram();
    glAttachShader(*shaderProgram, *vertexShader);
    glAttachShader(*shaderProgram, *fragmentShader);
    glLinkProgram(*shaderProgram);

    // Check for successfull compilation
    int full_shader_compilation;
    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &full_shader_compilation);

    if (!full_shader_compilation)
    {
        char infoLog[512];
        glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
    }
}