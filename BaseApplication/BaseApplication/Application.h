#pragma once



#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input.h"

namespace Hollow {


	class Application
	{



	public:

		Application();
		~Application();


		bool Init(const char* name, int w, int h);

		void Cleanup();

		void Run();





	private:

		void processInputs();



		GLFWwindow* window = nullptr;

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		float currentFrame = 0.0f;

		Input input;

	};

}