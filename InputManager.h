#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
class InputManager
{
private:
	GLFWwindow * window;
public:
	void registerKeyPress(void (*event)(GLFWwindow * win) ,int key);
	InputManager(GLFWwindow *win);

};



#endif
