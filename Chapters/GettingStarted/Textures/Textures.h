#pragma once

// ********************* INCLUDES *********************

#include "../../Exercises.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../../stb_image.h"

// ********************* TEXTURES IMPLEMENTATION *********************

void TexturesBase()
{
	// Create vertices for rectangle with colour and texture vertices
	float vertices[] = {
		// Position			  // Colour			  // Texture
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// Create and initialise the window
	auto window = Initialise();

	// Build and compile shader program
	Shader shader("Shaders/Vertex/Getting started/textures_vertex_shader.vs", "Shaders/Fragment/Getting started/textures_fragment_shader.fs");

	// Initialise the VBO, VAO, and EBO
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO, VBO, and EBO
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Modify the vertex format

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Initialise texture ID
	unsigned int texture_id;

	// Assign and bind texture
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	// Set texture wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering
	
	// Initialise image parameters
	int width, height, nrChannels;

	// Attempt to load the image to work in pixels
	unsigned char* data = stbi_load("Textures/Container.jpg", &width, &height, &nrChannels, 0);

	// Image is successfully loaded
	if (data)
	{
		// Attempt to generate texture and its mipmap
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: FAILED TO LOAD IMAGE" << std::endl;
	}

	// Perform cleanup of image
	stbi_image_free(data);
	
	// Attempt to display window by double-buffering
	while (!glfwWindowShouldClose(window))
	{
		// Check for input
		processInput(window);

		// Rendering commands
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Attempt to bind the texture
		glBindTexture(GL_TEXTURE_2D, texture_id);

		// Activate the shader
		shader.activate();

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
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
}

// ********************* TEXTURES EXERCISES *********************