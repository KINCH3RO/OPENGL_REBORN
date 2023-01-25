#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
class WindowManager
{
private:
	GLFWwindow	*window;
	size_t		screen_width;
	size_t		screen_height;
	char		*window_name;


public:
	GLFWwindow 		*initWindow();
	bool			loadGlad();
	void			setResizeEvent();
	WindowManager(int width, int height, char *name);
	~WindowManager();
};

#endif
