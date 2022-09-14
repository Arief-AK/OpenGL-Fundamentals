#pragma once

// ********************* INCLUDES *********************

#include "../../Exercises.h"

// ********************* CAMERA IMPLEMENTATION *********************

void CameraBaseImplementation()
{
	// Initialise the vertices for the 3D cube
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	// Initialise the positions of each cube
	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// Create and initialise the window
	auto window = Initialise();

	// Enable depth-buffer for OpenGL to remember which pixels are already coloured or not
	glEnable(GL_DEPTH_TEST);

	// Build and compile shader program
	Shader shader("Shaders/Vertex/Getting started/coordinate_systems_vertex_shader.vs", "Shaders/Fragment/Getting started/coordinate_systems_fragment_shader.fs");

	// Initialise the VBO, VAO, and EBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind VAO, VBO, and EBO
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Modify the vertex format

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Initialise texture ID
	unsigned int texture_0, texture_1;

	// Initialise image parameters
	int width, height, nrChannels;

	// Assign texture
	glGenTextures(1, &texture_0);
	glBindTexture(GL_TEXTURE_2D, texture_0);

	// Set texture wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping

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

	stbi_image_free(data_0);

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
	shader.setFloat("display_value", 0.2f);

	// Attempt to display window by double-buffering
	while (!glfwWindowShouldClose(window))
	{
		// Check for input
		processInput(window);

		// Clear depth buffer of vertices from the previous frame
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rendering commands
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Attempt to bind the texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_1);

		// Activate the shader
		shader.activate();

		// ********************* CAMERA CONFIGURATION *********************

		// Initialise the camera position
		glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 3.0f);

		// Initialise the camera target and direction
		glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 camera_direction = glm::normalize(camera_position - camera_target);

		// Initialise positive x-axis vector
		glm::vec3 up_axis = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 camera_right = glm::normalize(glm::cross(up_axis, camera_direction));

		// Initialise the positive y-axis
		glm::vec3 camera_up = glm::cross(camera_direction, camera_right);

		// ********************* VIEW SPACE MATRIXES *********************

		// Define radius
		float radius = 10.0f;

		// Perform trignometry calculations
		float cam_x = sin(glfwGetTime())* radius;
		float cam_y = cos(glfwGetTime())* radius;

		// Initialise matrix for view
		glm::mat4 view = glm::lookAt(glm::vec3(cam_x, 0.0f, cam_y), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		// Assign uniform to shader
		shader.setMat4("view", view);

		// ********************* WORLD SPACE MATRIXES *********************

		// Initialise the projection matrix to define projection frutsum
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		// Assign uniform to shader
		shader.setMat4("projection", projection);

		// Attempt to bind the vertex array
		glBindVertexArray(VAO);

		// ********************* INITIALISE CUBES *********************

		for (unsigned int i = 0; i < 10; i++)
		{
			// Initialise matrix for model
			glm::mat4 model = glm::mat4(1.0f);

			// Translate the models to different places in the world
			model = glm::translate(model, cubePositions[i]);

			// Always rotate model to replicate ground
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

			// Assign uniform to shader
			shader.setMat4("model", model);

			// Draw the elements using vertices
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Show on display
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Perform cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
}