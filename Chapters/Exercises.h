#pragma once

// ********************* INCLUDES *********************
#include "../Shaders/Shader.h"
#include "../Functions.h"

// ********************* BASE IMPLEMENTATION *********************

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

// ********************* CHAPTERS IMPLEMENTATION *********************

#include "GettingStarted/HelloTriangle/HelloTriangle.h"
#include "GettingStarted/Shaders/Shaders.h"
#include "GettingStarted/Textures/Textures.h"