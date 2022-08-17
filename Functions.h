#pragma once

// ********************* INCLUDES *********************
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

// ********************* GLOBALS *********************
bool wireframe = false;

// ********************* CHAPTER PREREQUISITES *********************

// ********************* HELLO TRIANGLE *********************
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\0";

const char* fragmentShaderSecondSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
"}\0";

// ********************* SHADERS *********************

const char* vertexShaderSecondSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\0";

const char* vertexShaderColoredVertexSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"     // Position variable
"layout (location = 1) in vec3 aColor;\n"   // Color variable
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"                   // Set ourColor to input color from the vertex data
"}\0";

const char* UniformFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\0";

const char* fragmentShaderColoredVertexSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
"}\0";

// ********************* FUNCTION DECLARATIONS *********************

// Callback function that is performed when a frame is created
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Function to process keyboard inputs
void processInput(GLFWwindow* window);

// Function to initialise the main window
GLFWwindow* Initialise();

// Function to initialise shaders
void InitialiseShaders(unsigned int* vertexShader, unsigned int* fragmentShader);

// Function to initilaise shader program
void InitialiseShaderProgram(unsigned int* vertexShader, unsigned int* fragmentShader, unsigned int* shaderProgram);

// Function to configure vertex buffer and arrray objects with overload function for indices compatibility
void BufferAndArrayConfiguration(unsigned int* VBO, unsigned int* VAO, float* vertices, unsigned long long size_vertices);
void BufferAndArrayConfiguration(unsigned int* VBO, unsigned int* VAO, unsigned int* EBO, float* vertices, unsigned int* indices, unsigned long long size_vertices, unsigned long long size_indices);

// ********************* FUNCTION IMPLEMENTATION *********************
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Assign respective width and height of window
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    // Check for escape key press
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Check for wireframe key press
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if (!wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            wireframe = true;
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            wireframe = false;
        }
    }
}

// ********************* HELPER FUNCTIONS *********************

GLFWwindow* Initialise()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Attempt to create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // Attempt to intialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    return window;
}

void InitialiseShaders(unsigned int* vertexShader, unsigned int* fragmentShader)
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

void InitialiseShaders(unsigned int* vertexShader, unsigned int* fragmentShader, const char* vertexShaderSource, const char* fragmentShaderSource)
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

void InitialiseShaderProgram(unsigned int* vertexShader, unsigned int* fragmentShader, unsigned int* shaderProgram)
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

    // Perform cleanup of shaders
    glDeleteShader(*vertexShader);
    glDeleteShader(*fragmentShader);
}

void BufferAndArrayConfiguration(unsigned int* VBO, unsigned int* VAO, float* vertices, unsigned long long size_vertices)
{
    // ********************* VERTICES AND BUFFER ARRAY CONFIGURATIONS *********************

    // Generate buffers and vertex arrays
    glGenBuffers(1, VBO);
    glGenVertexArrays(1, VAO);

    // Attempt to bind vertex array and buffer
    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);

    // Attempt to copy the vertex data
    glBufferData(GL_ARRAY_BUFFER, size_vertices, vertices, GL_STATIC_DRAW);

    // Configure the vertex attributes and enable the vertex array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Attempt to unbind buffer and vertex array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void BufferAndArrayConfiguration(unsigned int* VBO, unsigned int* VAO, unsigned int* EBO, float* vertices, unsigned int* indices, unsigned long long size_vertices, unsigned long long size_indices)
{
    // ********************* VERTICES AND BUFFER ARRAY CONFIGURATIONS *********************

    // Generate buffers and vertex arrays
    glGenBuffers(1, VBO);
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, EBO);

    // Attempt to bind vertex array
    glBindVertexArray(*VAO);

    // Attempt to bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);

    // Attempt to copy the vertex data
    glBufferData(GL_ARRAY_BUFFER, size_vertices, vertices, GL_STATIC_DRAW);

    // Attempt to bind buffer and data of the Element Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_indices, indices, GL_STATIC_DRAW);

    // Configure the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Attempt to bind buffer and vertex array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}