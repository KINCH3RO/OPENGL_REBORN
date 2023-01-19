#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include "WindowManager.h"
#include "InputManager.h"
#include "shader.h"
#include <math.h>
int main(void)
{

	GLFWwindow *window;
	unsigned int VBO, VAO;

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f};

	WindowManager winMG(800, 600, "OPENGL_REBORN");
	window = winMG.initWindow();
	InputManager inputMG(window);
	winMG.loadGlad();
	winMG.setResizeEvent();
	// generating 1 vertex array object so store all vbo and attrib pointer config with id vao
	glGenVertexArrays(1, &VAO);
	// binding vertex array
	glBindVertexArray(VAO);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	// enabling the location of it
	glEnableVertexAttribArray(0);
	// configuring how data should be interpreted from the gpu (verticies colors) starting from byte (3 * sizeof(float) = 24)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	// enabling the location of it
	glEnableVertexAttribArray(1);

	// unbound any vertex array for later user
	glBindVertexArray(0);
	// fragment shader and vertex shader source code

	// replacing vertex shader and fragment shader compilation with abstract class
	Shader shaderProgram("./shaders_src/shader_chapter_shaders/vertexShader.glsl",
						 "./shaders_src/shader_chapter_shaders/fragmentShader.glsl");
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
		// draawing with peremetive GL_TRIANGLE starting for vertex 0 and draw 3 verticies
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// swap double buffres
		glfwSwapBuffers(window);
		// check for events
		glfwPollEvents();
	}

	return 0;
}
