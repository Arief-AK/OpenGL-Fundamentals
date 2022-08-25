#pragma once

// ********************* INCLUDES *********************
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Functions.h"

// ********************* CHAPTERS IMPLEMENTATION *********************

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

// ********************* HELLO TRIANGLE EXERCISES *********************

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

// Base uniform shader implementation
void BaseUniformShader()
{
    unsigned int vertexShader, fragmentShader, shaderProgram;

    // Vertices for triangle
    float vertices[] = {
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f   // top 
    };

    // Get the size of vertices
    auto size_vertices = sizeof(vertices);

    // Create and initialise the window
    auto window = Initialise();

    // Initialise shaders
    InitialiseShaders(&vertexShader, &fragmentShader, vertexShaderSource, UniformFragmentShaderSource);
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

        // Update shader program

        // Get running time
        double timeValue = glfwGetTime();

        // Attempt to vary the red part colour
        float red_value = (sin(timeValue) / 2.0f) + 0.5f;

        // Get location of the uniform variable
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        glUniform4f(vertexColorLocation, red_value, 0.0f, 0.0f, 1.0f);

        // Attempt to bind the vertex array
        glBindVertexArray(VAO);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

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

// Separate colour for each vertex
void ColouredVertex()
{
    unsigned int vertexShader, fragmentShader, shaderProgram;

    // Vertices for triangle
    float vertices[] = {
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right with red colour
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left with blue colour
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top with green colour
    };

    // Get the size of vertices
    auto size_vertices = sizeof(vertices);

    // Create and initialise the window
    auto window = Initialise();

    // Initialise shaders
    InitialiseShaders(&vertexShader, &fragmentShader, vertexShaderColoredVertexSource, fragmentShaderColoredVertexSource);
    InitialiseShaderProgram(&vertexShader, &fragmentShader, &shaderProgram);

    // Create OpenGL buffer and array
    unsigned int VBO, VAO;

    // ********************* VERTICES AND BUFFER ARRAY CONFIGURATIONS *********************

    // Generate buffers and vertex arrays
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // Attempt to bind vertex array and buffer
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Attempt to copy the vertex data
    glBufferData(GL_ARRAY_BUFFER, size_vertices, vertices, GL_STATIC_DRAW);

    // Configure the vertex attributes and enable the vertex array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // For position, modified to accomodate color data
    glEnableVertexAttribArray(0);

    // Confifgure to accomodate the position data
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Use shader program
    glUseProgram(shaderProgram);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Perform cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

// Shader class implementation
void ShaderClassImplementation()
{
    // Vertices for triangle
    float vertices[] = {
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right with red colour
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left with blue colour
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top with green colour
    };

    // Get the size of vertices
    auto size_vertices = sizeof(vertices);

    // Create and initialise the window
    auto window = Initialise();

    // Build and compile shader program
    Shader shader("vertex_shader.vs", "fragment_shader.fs");

    // Create OpenGL buffer and array
    unsigned int VBO, VAO;

    // ********************* VERTICES AND BUFFER ARRAY CONFIGURATIONS *********************

    // Generate buffers and vertex arrays
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // Attempt to bind vertex array and buffer
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Attempt to copy the vertex data
    glBufferData(GL_ARRAY_BUFFER, size_vertices, vertices, GL_STATIC_DRAW);

    // Configure the vertex attributes and enable the vertex array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // For position, modified to accomodate color data
    glEnableVertexAttribArray(0);

    // Confifgure to accomodate the position data
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader program
        shader.activate();

        // Rendering
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Perform cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
}

// ********************* SHADERS EXERCISES *********************

// Exercise 1 implementation
void ShaderExercise1()
{
    // Vertices for triangle
    float vertices[] = {
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right with red colour
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left with blue colour
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top with green colour
    };

    // Get the size of vertices
    auto size_vertices = sizeof(vertices);

    // Create and initialise the window
    auto window = Initialise();

    // Build and compile shader program
    Shader shader("Shaders/Vertex/vertex_shader.vs", "Shaders/Fragment/fragment_shader.fs");

    // Create OpenGL buffer and array
    unsigned int VBO, VAO;

    // ********************* VERTICES AND BUFFER ARRAY CONFIGURATIONS *********************

    // Generate buffers and vertex arrays
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // Attempt to bind vertex array and buffer
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Attempt to copy the vertex data
    glBufferData(GL_ARRAY_BUFFER, size_vertices, vertices, GL_STATIC_DRAW);

    // Configure the vertex attributes and enable the vertex array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // For position, modified to accomodate color data
    glEnableVertexAttribArray(0);

    // Confifgure to accomodate the position data
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader program
        shader.activate();

        // Rendering
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Perform cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
}

void ShaderExercise2(float horizontal_offset)
{
    // Vertices for triangle
    float vertices[] = {
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right with red colour
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left with blue colour
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top with green colour
    };

    // Get the size of vertices
    auto size_vertices = sizeof(vertices);

    // Create and initialise the window
    auto window = Initialise();

    // Build and compile shader program
    Shader shader("Shaders/Vertex/vertex_shader_ex2.vs", "Shaders/Fragment/fragment_shader.fs");

    // Create OpenGL buffer and array
    unsigned int VBO, VAO;

    // ********************* VERTICES AND BUFFER ARRAY CONFIGURATIONS *********************

    // Generate buffers and vertex arrays
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // Attempt to bind vertex array and buffer
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Attempt to copy the vertex data
    glBufferData(GL_ARRAY_BUFFER, size_vertices, vertices, GL_STATIC_DRAW);

    // Configure the vertex attributes and enable the vertex array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // For position, modified to accomodate color data
    glEnableVertexAttribArray(0);

    // Confifgure to accomodate the position data
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.setFloat("my_offset", horizontal_offset);

        // Use shader program
        shader.activate();

        // Rendering
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Perform cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
}

void ShaderExercise3()
{
    // Vertices for triangle
    float vertices[] = {
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right with red colour
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left with blue colour
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top with green colour
    };

    // Get the size of vertices
    auto size_vertices = sizeof(vertices);

    // Create and initialise the window
    auto window = Initialise();

    // Build and compile shader program
    Shader shader("Shaders/Vertex/vertex_shader_ex3.vs", "Shaders/Fragment/fragment_shader_ex3.fs");

    // Create OpenGL buffer and array
    unsigned int VBO, VAO;

    // ********************* VERTICES AND BUFFER ARRAY CONFIGURATIONS *********************

    // Generate buffers and vertex arrays
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // Attempt to bind vertex array and buffer
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Attempt to copy the vertex data
    glBufferData(GL_ARRAY_BUFFER, size_vertices, vertices, GL_STATIC_DRAW);

    // Configure the vertex attributes and enable the vertex array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // For position, modified to accomodate color data
    glEnableVertexAttribArray(0);

    // Confifgure to accomodate the position data
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader program
        shader.activate();

        // Rendering
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Perform cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
}
