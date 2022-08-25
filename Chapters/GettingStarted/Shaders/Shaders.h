#pragma once

// ********************* INCLUDES *********************

#include "../../Exercises.h"

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
    Shader shader("Shaders/Vertex/Getting started/vertex_shader.vs", "Shaders/Fragment/Getting started/fragment_shader.fs");

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
    Shader shader("Shaders/Vertex/Getting started/vertex_shader_ex2.vs", "Shaders/Fragment/Getting started/fragment_shader.fs");

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
    Shader shader("Shaders/Vertex/Getting started/vertex_shader_ex3.vs", "Shaders/Fragment/Getting started/fragment_shader_ex3.fs");

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