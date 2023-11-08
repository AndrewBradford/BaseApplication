#include "Application.h"


#include <iostream>


#include "StateBase.h"

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

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->input.mousex = xpos;
		app->input.mousey = ypos;

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


		glfwSetWindowUserPointer(window, this);

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);




		lastFrame = glfwGetTime();


		currentState = new Hollow::StateBase();


		glEnable(GL_DEPTH_TEST);

		return true;

	}

	void Application::Cleanup()
	{

		glfwTerminate();
		currentState->~StateBase();

	}

	void Application::Run()
	{



		currentState->Init(window);

		// the game loop
		while (!glfwWindowShouldClose(window))
		{
			//calculate the frame time
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			std::cout << 1.f / deltaTime << " FPS" << std::endl;


			//check for changing state?


			//deal with inputs
			processInputs();

			//update current state + render
			currentState->frame(deltaTime, window, &input);


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


		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			input.setKeyDown(Input::KEYS::W);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
		{
			input.setKeyUp(Input::KEYS::W);
		}
		
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			input.setKeyDown(Input::KEYS::S);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
		{
			input.setKeyUp(Input::KEYS::S);
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			input.setKeyDown(Input::KEYS::D);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
		{
			input.setKeyUp(Input::KEYS::D);
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			input.setKeyDown(Input::KEYS::A);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
		{
			input.setKeyUp(Input::KEYS::A);
		}

	}




}

