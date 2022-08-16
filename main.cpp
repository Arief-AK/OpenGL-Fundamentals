// ********************* INCLUDES *********************
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

// ********************* GLOBALS *********************
bool wireframe = false;

// ********************* OPENGL PREREQUISITES *********************
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

// ********************* FUNCTION DECLARATIONS *********************
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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

// ********************* EXERCISES IMPLEMENTATION *********************

// Base implementation
void Base()
{
    unsigned int vertexShader, fragmentShader, shaderProgram;

    // Create vertices for rectangle
    float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };

    auto size_vertices = sizeof(vertices);
    auto size_indices = sizeof(indices);

    auto window = Initialise();

    // Initialise shaders
    InitialiseShaders(&vertexShader, &fragmentShader);
    InitialiseShaderProgram(&vertexShader, &fragmentShader, &shaderProgram);

    // Create OpenGL buffer and array
    unsigned int VBO, VAO, EBO;
    BufferAndArrayConfiguration(&VBO, &VAO, &EBO, vertices, indices, size_vertices, size_indices);

    // Attempt to display window by double-buffering
    while (!glfwWindowShouldClose(window))
    {
        // Check for input
        processInput(window);

        // Rendering commands
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Assign shader program
        glUseProgram(shaderProgram);

        // Attempt to bind the vertex array
        glBindVertexArray(VAO);

        // Draw the elements
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Show on display
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Perform cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

// Exercise 1 implementation
void Exercise1()
{
    unsigned int vertexShader, fragmentShader, shaderProgram;

    // Create vertices for the two triangles
    float vertices[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
        // second triangle
         0.0f, -0.5f, 0.0f,  // left
         0.9f, -0.5f, 0.0f,  // right
         0.45f, 0.5f, 0.0f   // top 
    };

    auto size_vertices = sizeof(vertices);
    auto window = Initialise();

    // Initialise shaders
    InitialiseShaders(&vertexShader, &fragmentShader);
    InitialiseShaderProgram(&vertexShader, &fragmentShader, &shaderProgram);

    // Create OpenGL buffer and array
    unsigned int VBO, VAO;
    BufferAndArrayConfiguration(&VBO, &VAO, vertices, size_vertices);

    // Attempt to display window by double-buffering
    while (!glfwWindowShouldClose(window))
    {
        // Check for input
        processInput(window);

        // Rendering commands
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Assign shader program
        glUseProgram(shaderProgram);

        // Attempt to bind the vertex array
        glBindVertexArray(VAO);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Show on display
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Perform cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

// Exercise 2 implementation
void Exercise2()
{
    // Predefine shaders
    unsigned int vertexShader, fragmentShader, shaderProgram;

    // Create two separate vertices for the two triangles
    float first_triangle[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f
    };

    float second_triangle[] = {
        0.0f, -0.5f, 0.0f,  // left
         0.9f, -0.5f, 0.0f,  // right
         0.45f, 0.5f, 0.0f
    };

    // Get the sizes
    auto size_first_triangle = sizeof(first_triangle);
    auto size_second_triangle = sizeof(second_triangle);

    // Create the window
    auto window = Initialise();

    // Initialise shaders
    InitialiseShaders(&vertexShader, &fragmentShader);
    InitialiseShaderProgram(&vertexShader, &fragmentShader, &shaderProgram);

    // Create explicit VBO and VAO for the triangles
    unsigned int VBO[2];
    unsigned int VAO[2];

    BufferAndArrayConfiguration(&VBO[0], &VAO[0], first_triangle, size_first_triangle);
    BufferAndArrayConfiguration(&VBO[1], &VAO[1], second_triangle, size_second_triangle);

    // Attempt to display window by double-buffering
    while (!glfwWindowShouldClose(window))
    {
        // Check for input
        processInput(window);

        // Rendering commands
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Assign shader program
        glUseProgram(shaderProgram);

        // Draw the first triangle
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // Draw the second triangle
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Show on display
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Perform cleanup
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

// Exercise 3 implementation
void Exercise3()
{
    // Predefine shaders
    unsigned int vertexShader;
    unsigned int fragmentShaders[2];
    unsigned int shaderPrograms[2];

    // Create two separate vertices for the two triangles
    float first_triangle[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f
    };

    float second_triangle[] = {
        0.0f, -0.5f, 0.0f,  // left
         0.9f, -0.5f, 0.0f,  // right
         0.45f, 0.5f, 0.0f
    };

    // Get the sizes
    auto size_first_triangle = sizeof(first_triangle);
    auto size_second_triangle = sizeof(second_triangle);

    // Create the window
    auto window = Initialise();

    // ********************* VERTEX SHADER *********************

    // Create and compile vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for compilation error
    int successful_vertex_compilation;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successful_vertex_compilation);

    if (!successful_vertex_compilation)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ********************* FRAGMENT SHADERS *********************

    // Create and compile first fragment shader
    fragmentShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaders[0], 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaders[0]);

    // Check for compilation error
    int successful_fragment_compilation;
    glGetShaderiv(fragmentShaders[0], GL_COMPILE_STATUS, &successful_fragment_compilation);

    if (!successful_fragment_compilation)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShaders[0], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // Create and compile second fragment shader
    fragmentShaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaders[1], 1, &fragmentShaderSecondSource, NULL);
    glCompileShader(fragmentShaders[1]);

    // Check for compilation error
    int successful_second_fragment_compilation;
    glGetShaderiv(fragmentShaders[0], GL_COMPILE_STATUS, &successful_second_fragment_compilation);

    if (!successful_second_fragment_compilation)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShaders[1], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ********************* SHADER PROGRAMS *********************
    
    // Create and compile first shader program
    shaderPrograms[0] = glCreateProgram();
    glAttachShader(shaderPrograms[0], vertexShader);
    glAttachShader(shaderPrograms[0], fragmentShaders[0]);
    glLinkProgram(shaderPrograms[0]);

    // Check for successfull compilation
    int first_shader_compilation;
    glGetProgramiv(shaderPrograms[0], GL_LINK_STATUS, &first_shader_compilation);

    if (!first_shader_compilation)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderPrograms[0], 512, NULL, infoLog);
    }

    // Create and compile second shader program
    shaderPrograms[1] = glCreateProgram();
    glAttachShader(shaderPrograms[1], vertexShader);
    glAttachShader(shaderPrograms[1], fragmentShaders[1]);
    glLinkProgram(shaderPrograms[1]);

    // Check for successfull compilation
    int second_shader_compilation;
    glGetProgramiv(shaderPrograms[1], GL_LINK_STATUS, &second_shader_compilation);

    if (!second_shader_compilation)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderPrograms[1], 512, NULL, infoLog);
    }

    // ********************* VERTEX BUFFER AND ARRAY CONFIGURATIONS *********************

    // Perform cleanup of shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaders[0]);
    glDeleteShader(fragmentShaders[1]);

    // Create explicit VBO and VAO for the triangles
    unsigned int VBO[2];
    unsigned int VAO[2];

    BufferAndArrayConfiguration(&VBO[0], &VAO[0], first_triangle, size_first_triangle);
    BufferAndArrayConfiguration(&VBO[1], &VAO[1], second_triangle, size_second_triangle);

    // Attempt to display window by double-buffering
    while (!glfwWindowShouldClose(window))
    {
        // Check for input
        processInput(window);

        // Rendering commands
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Assign shader to the first shader program for first triangle
        glUseProgram(shaderPrograms[0]);

        // Draw the first triangle
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Assign shader to the second shader program for second triangle
        glUseProgram(shaderPrograms[1]);

        // Draw the second triangle
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Show on display
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Perform cleanup
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteProgram(shaderPrograms[0]);
    glDeleteProgram(shaderPrograms[1]);
    glfwTerminate();
}

// ********************* MAIN PROGRAM *********************

int main()
{
    bool quit = false;
    int response = -1;

    while (!quit)
    {
        std::cout << "\nEnter option:\n";
        std::cout << "0) Base\n";
        std::cout << "1) Exercise 1\n";
        std::cout << "2) Exercise 2\n";
        std::cout << "3) Exercise 3\n";
        std::cout << "4) Quit\n";
        std::cout << "\nOption:";
        std::cin >> response;

        switch (response)
        {
        case 0: 
            Base();
            break;
        case 1:
            Exercise1();
            break;
        case 2:
            Exercise2();
            break;
        case 3:
            Exercise3();
            break;
        case 4:
            quit = true;
            break;
        default:
            Base();
            break;
        }
    }

    std::cout << "\nGood-bye!";
    return 0;
}