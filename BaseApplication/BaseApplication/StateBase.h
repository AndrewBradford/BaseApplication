#pragma once


#include "Shader.h"
#include "Geometry.h"
#include "Camera.h"
#include "Input.h"

#include <glm/glm.hpp>

#include "HyperEdgeGrammar.h"

namespace Hollow {




	class StateBase
	{

		struct Shaders {
			LitShader litShader;
			FlatShader flatShader;
			LineShader lineShader;
			TrajShader trajShader;
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


		void gui();

	private:

		Camera camera;

		Shaders shaders;

		VArray cubeVN;
		VArray cubeV;
		VArray line;
		VArray trajectory;

		GObject cube;
		GObject lightCube;

		GObject lineOb;

		Light light;

		HyperEdgeGrammar grammar;

		//gui variables
		float frameTime = 0.0f;
		bool debugBool = false;
		bool wireFrameToggle = false;

		glm::vec3 line_start;
		glm::vec3 line_end;

		float velocity;
		float angle;
		float gravity;

		glm::vec3 point_pos;

		bool is_point_in;

		glm::vec3 yes_col;
		glm::vec3 no_col;

		glm::vec3 point_col;

		bool show_rotations = false;
		int traj_its = 10;
	};

}
