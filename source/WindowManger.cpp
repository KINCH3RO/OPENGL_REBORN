#include "include/WindowManager.h"

WindowManager::WindowManager(int width, int height, char *name)
{
	this->screen_width = width;
	this->screen_height = height;
	this->window_name = name;
}

GLFWwindow *WindowManager::initWindow()
{
	if (!glfwInit())
		std::cout << "couldn't initialize glfw ";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	this->window = glfwCreateWindow(this->screen_width, this->screen_height, this->window_name, NULL, NULL);

	if (!this->window)
		std::cout << "couldn't initialize glfw window";
	glfwMakeContextCurrent(this->window);
	return this->window;
}

bool WindowManager::loadGlad()
{
	bool gladStatus = !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (gladStatus)
		std::cout << "failed to initialize glad";
	else
		glViewport(0, 0, this->screen_width, this->screen_height);
	return gladStatus;
}

void WindowManager::setResizeEvent()
{
	glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow *window, int width, int height) -> void
								   { glViewport(0, 0, width, height); });
}

WindowManager::~WindowManager()
{
	glfwTerminate();
}
