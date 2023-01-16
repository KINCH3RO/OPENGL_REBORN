#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include "WindowManager.h"
#include "InputManager.h"

int main(void)
{

	WindowManager winMG(800, 800, "OPENGL_REBORN");
	GLFWwindow *window = winMG.initWindow();
	InputManager inputMG(window);
	winMG.loadGlad();
	winMG.setResizeEvent();

	while (!glfwWindowShouldClose(window))
	{
		// process input
		inputMG.registerKeyPress([](GLFWwindow *win) -> void
								 { glfwSetWindowShouldClose(win, true); },
								 GLFW_KEY_ESCAPE);
		// rendering goes here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// swap double buffres
		glfwSwapBuffers(window);
		// check for events
		glfwPollEvents();
	}

	return 0;
}
