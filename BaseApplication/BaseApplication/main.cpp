

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Window.h"
#include "Renderer.h"
#include "Input.h"


int main()
{


	Input input;
	Window window;
	Renderer renderer;

	window.createWindowGL("Base Application", 800, 600);



	float delta = 0.0f;
	while (!window.ShouldClose())
	{

		delta = window.getDeltaTime();
		std::cout << 1.f / delta << " FPS\n";




		window.endFrame();

	}

	window.terminate();

}