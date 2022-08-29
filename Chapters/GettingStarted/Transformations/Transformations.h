#pragma once

// ********************* INCLUDES *********************

#include "../../Exercises.h"

// ********************* TRANSFORMATION IMPLEMENTATION *********************

void TransformationBase()
{
	// Create vertices for rectangle with colour and texture vertices
	float vertices[] = {
		// Position			  // Colour			  // Texture
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// Create and initialise the window
	auto window = Initialise();

	// Build and compile shader program
	Shader shader("Shaders/Vertex/Getting started/transformations_vertex_shader.vs", "Shaders/Fragment/Getting started/transformations_fragment_shader.fs");

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
	unsigned int texture_0, texture_1;

	// Initialise image parameters
	int width, height, nrChannels;

	// Assign texture
	glGenTextures(1, &texture_0);
	glBindTexture(GL_TEXTURE_2D, texture_0);

	// Set texture wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Wrapping

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering

	// Attempt to load the image to work in pixels
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data_0 = stbi_load("Textures/Container.jpg", &width, &height, &nrChannels, 0);

	// Attempt to load first image
	if (data_0)
	{
		// Attempt to generate texture and its mipmap
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_0);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: FAILED TO LOAD FIRST IMAGE" << std::endl;
	}

	glGenTextures(1, &texture_1);
	glBindTexture(GL_TEXTURE_2D, texture_1);

	// Set texture wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering

	data_0 = stbi_load("Textures/awesomeface.png", &width, &height, &nrChannels, 0);

	// Attempt to load second image
	if (data_0)
	{
		// Attempt to generate texture and its mipmaps
		// IMPORTANT: If the source image has transparancy, make sure to use the GL_RGBA with an aplha channel
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_0);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: FAILED TO LOAD SECOND IMAGE" << std::endl;
	}

	// Perform cleanup of image
	stbi_image_free(data_0);

	// Activate the shader
	shader.activate();

	// Set uniforms
	shader.setInt("texture_0", 0);
	shader.setInt("texture_1", 1);

	// Attempt to display window by double-buffering
	while (!glfwWindowShouldClose(window))
	{
		// Check for input
		processInput(window);

		// Rendering commands
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Attempt to bind the texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_1);

		// Set the uniform for the display_value
		shader.setFloat("display_value", 0.6f);

		// Activate the shader
		shader.activate();

		// ********************* TRANSFORMATION CALCULATIONS *********************

		// Initialise matrices
		glm::mat4 matrix_trans = glm::mat4(1.0f);

		// Translate matrix to the bottom right of the screen
		matrix_trans = glm::translate(matrix_trans, glm::vec3(0.5f, -0.5f, 0.0f));

		// Rotate matrix continously. Note that function 'glfwGetTime()' returns double. Casting to float required
		matrix_trans = glm::rotate(matrix_trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));

		// Scale matrix by 0.5
		matrix_trans = glm::scale(matrix_trans, glm::vec3(0.5, 0.5, 0.5));

		// Inform shader of matrix uniform
		shader.setMat4("transform", matrix_trans);

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