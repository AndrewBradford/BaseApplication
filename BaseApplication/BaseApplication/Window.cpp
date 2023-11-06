#include "Window.h"


Window::Window()
{
}

Window::~Window()
{
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool Window::createWindowGL(const char* name, int w, int h)
{

	// start the window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(w, h, name, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create glfw window" << std::endl;
		glfwTerminate();
		return false;
	}

	// create opengl context
	glfwMakeContextCurrent(window);

	// initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (glfwRawMouseMotionSupported())
	{
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}


	//glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	lastFrame = glfwGetTime();

	return false;
}



void Window::registerFramebufferSizeCallback(GLFWframebuffersizefun callback)
{
	glfwSetFramebufferSizeCallback(window, callback);
}

void Window::registerCursorPosCallback(GLFWcursorposfun callback)
{
	glfwSetCursorPosCallback(window, callback);
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::CloseWindow()
{
	glfwSetWindowShouldClose(window, true);
}

void Window::terminate()
{
	glfwTerminate();
}

float Window::getDeltaTime()
{
	currentFrame = glfwGetTime();
	float dt = currentFrame - lastFrame;
	lastFrame = currentFrame;
	return dt;
}

void Window::endFrame()
{

	glfwSwapBuffers(window);
	glfwPollEvents();

}
