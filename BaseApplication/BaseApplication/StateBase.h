#pragma once


#include "Shader.h"
#include "Geometry.h"
#include "Camera.h"
#include "Input.h"

#include <glm/glm.hpp>

namespace Hollow {




	class StateBase
	{

		struct Shaders {
			LitShader litShader;
			FlatShader flatShader;
		};

		struct GObject {
			glm::vec3 color;
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;
		};

		struct Light {
			glm::vec3 color;
			glm::vec3 position;
		};

	public:

		StateBase();
		~StateBase();

		void Init(GLFWwindow* window);

		void frame(float dt, GLFWwindow* window, Input* in);

		void processInput(float dt, GLFWwindow* window, Input* in);

		void Cleanup();


	private:

		Camera camera;

		Shaders shaders;

		VArray cubeVN;
		VArray cubeV;

		GObject cube;
		GObject lightCube;

		Light light;


	};

}
