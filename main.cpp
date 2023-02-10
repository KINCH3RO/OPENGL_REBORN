#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include "WindowManager.h"
#include "InputManager.h"
#include "Shader.h"
#include "stb_image.h"
#include <math.h>
int main(void)
{

	GLFWwindow *window;
	unsigned int VBO, VAO, EBO;

	float vertices[] = {
		// positions          // colors           // texture coords
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	  // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f	  // top left
	};

	unsigned int indices[] = {
		// note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3	 // second triangle
	};

	WindowManager winMG(800, 600, "OPENGL_REBORN");
	window = winMG.initWindow();
	InputManager inputMG(window);
	winMG.loadGlad();
	winMG.setResizeEvent();
	// generating 1 vertex array object so store all vbo and attrib pointer config with id vao
	glGenVertexArrays(1, &VAO);
	// binding vertex array
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// generating 1  buffer that has id VBO
	glGenBuffers(1, &VBO);
	// Binding buffer to configure it using gl bind buffer of type VERTEX BUFFER OBJECT (GL_ARRAY_BUFFER)
	// VERTEX BUFFER OBJECT is an object that can store data and sent id to the GPU Memory
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// copying data to the BUFFER
	// send data to gpu
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// third parameter of glBufferData
	// GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
	// GL_STATIC_DRAW: the data is set only once and used many times.
	// GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
	// configuring how data should be interpreted from the gpu (verticies position) starting from byte 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	// enabling the location of it
	glEnableVertexAttribArray(0);
	// configuring how data should be interpreted from the gpu (verticies colors) starting from byte (3 * sizeof(float) = 24)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	// enabling the location of it
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	// enabling the location of it
	glEnableVertexAttribArray(2);

	// unbound any vertex array for later user
	glBindVertexArray(0);
	// fragment shader and vertex shader source code

	// replacing vertex shader and fragment shader compilation with abstract class
	Shader shaderProgram("./shaders_src/texture_chapter_shaders/vertexShader.glsl",
						 "./shaders_src/texture_chapter_shaders/fragmentShader.glsl");

	// textures
	int width, height, nrChannels;

	unsigned int texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char *data = stbi_load("resources/textures/container.jpg", &width, &height, &nrChannels, 0);
	if (!data)
		std::cout << "failed to load textures\n";
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	///
	shaderProgram.use();
	glBindVertexArray(VAO);
	std::cout << "yes\n";
	while (!glfwWindowShouldClose(window))
	{

		// process input
		inputMG.registerKeyPress([](GLFWwindow *win) -> void
								 { glfwSetWindowShouldClose(win, true); },
								 GLFW_KEY_ESCAPE);
		// rendering goes here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//wrireframem mode
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// swap double buffres
		glfwSwapBuffers(window);
		// check for events
		glfwPollEvents();
	}

	return 0;
}
