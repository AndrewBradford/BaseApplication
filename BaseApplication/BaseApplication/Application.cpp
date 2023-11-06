#include "Application.h"


#include <iostream>


namespace Hollow {




	Application::Application()
	{
	}

	Application::~Application()
	{
	}


	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	bool Application::Init(const char* name, int w, int h)
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


		return true;

	}

	void Application::Cleanup()
	{

		glfwTerminate();

	}

	void Application::Run()
	{



		// the game loop
		while (!glfwWindowShouldClose(window))
		{
			//calculate the frame time
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			std::cout << 1.f / deltaTime << " FPS" << std::endl;


			//check for changing state


			//deal with inputs
			processInputs();

			//update current state


			//render the current state


			//end of frame stuff
			glfwSwapBuffers(window);
			glfwPollEvents();

		}




	}


	//process inputs and pass 
	void Application::processInputs()
	{


		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}


	}

}