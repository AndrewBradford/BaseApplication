#pragma once



#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input.h"

namespace Hollow {


	class StateBase;

	class Application
	{



	public:

		Application();
		~Application();


		bool Init(const char* name, int w, int h);

		void Cleanup();

		void Run();


		Input input;


	private:

		void processInputs();


		GLFWwindow* window = nullptr;

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		float currentFrame = 0.0f;


		Hollow::StateBase* currentState;

	};

}