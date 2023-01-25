#include "include/InputManager.h"

InputManager::InputManager(GLFWwindow *win)
{
	this->window = win;
}

void InputManager::registerKeyPress(void (*event)(GLFWwindow *win), int key)
{
	if (glfwGetKey(this->window, key) == GLFW_PRESS)
		event(this->window);
}
