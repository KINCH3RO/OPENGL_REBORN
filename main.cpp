#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include "WindowManager.h"
#include "InputManager.h"

int main(void)
{

	GLFWwindow *window;
	unsigned int VBO,VAO, vertexShader, fragmentShader, shaderProgram;
	// store shadeer info
	int success;
	char infoLog[512];

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f};

	WindowManager winMG(800, 600, "OPENGL_REBORN");
	window = winMG.initWindow();
	InputManager inputMG(window);
	winMG.loadGlad();
	winMG.setResizeEvent();
	//generating 1 vertex array object so store all vbo and attrib pointer config with id vao
	glGenVertexArrays(1,&VAO);
	//binding vertex array
	glBindVertexArray(VAO);


	// generating 1  buffer that has id VBO
	glGenBuffers(1, &VBO);
	// Binding buffer to configure it using gl bind buffer of type VERTEX BUFFER OBJECT (GL_ARRAY_BUFFER)
	// VERTEX BUFFER OBJECT is an object that can store data and sent id to the GPU Memory
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// copying data to the BUFFER
	//send data to gpu
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// third parameter of glBufferData
	// GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
	// GL_STATIC_DRAW: the data is set only once and used many times.
	// GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
	// configuring how data should be interpreted from the gpu
	glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void *)0);
	//enabling the location of it
	glEnableVertexAttribArray(0);
	//unbound any vertex array for later user
	glBindVertexArray(0);
	//fragment shader and vertex shader source code
	const char *vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "void main()\n"
									 "{\n"
									 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
									 "}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
									   "out vec4 FragColor\n;"
									   "void main()\n"
									   "{\n"
									   "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
									   "}\0";
	// creating vertex shader and handling errors
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	// creating fragment shader and handling errors
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	//shaders need to be linked with a shader program for later use
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	//unbounding any shader program
	glUseProgram(0);
	//liberating ressources
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//binding the vertex array and shader program
	glBindVertexArray(VAO);
	glUseProgram(shaderProgram);

	while (!glfwWindowShouldClose(window))
	{
		// process input
		inputMG.registerKeyPress([](GLFWwindow *win) -> void
								 { glfwSetWindowShouldClose(win, true); },
								 GLFW_KEY_ESCAPE);
		// rendering goes here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//draawing with peremetive GL_TRIANGLE starting for vertex 0 and draw 3 verticies
		glDrawArrays(GL_TRIANGLES,0,3);
		// swap double buffres
		glfwSwapBuffers(window);
		// check for events
		glfwPollEvents();
	}

	return 0;
}
