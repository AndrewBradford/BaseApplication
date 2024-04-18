#pragma once


#include "Shader.h"
#include "Geometry.h"
#include "Camera.h"
#include "Input.h"

#include <glm/glm.hpp>

#include "HyperEdgeGrammar.h"

#include <vector>

#include "Physics.h"

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


		void gui(GLFWwindow* window);

		void draw_space_graph();
		void DrawTrajectoryDemo();
		void DrawLevel();

	private:

		void ShowMainControls(GLFWwindow* window);
		void ShowTrajectoryDemoControls();
		void ShowExampleLevelControls();
		void ShowDataCollectionControls();
		void ShowGraphs();


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

		Physics phys;

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
		glm::vec3 closest_point_pos;
		glm::vec3 point_offset;

		bool is_point_in;


		glm::vec3 yes_col;
		glm::vec3 no_col;

		glm::vec3 point_col;
		glm::vec3 plat_col;
		glm::vec3 start_col;
		glm::vec3 end_col;
		glm::vec3 hyper_col;

		bool calc_closest_point = false;

		bool show_lines = true;
		bool show_constraints = true;
		bool physics_updates = false;

		float speed = 20.f;

		bool show_rotations = false;
		int traj_its = 10;

		float point_angle = 0;
		float point_mag = 1;
		float point_height = 0;


		float xs[3] = { 0,1,2 };
		float ys[3] = { 5,10,2 };

		float traj_xs[1000];
		float traj_ys[1000];

		float dist_xs[1000];
		float dist_ys[1000];

		float dist_root_xs[1000];
		float dist_root_ys[1000];

		float der_xs[1000];
		float der_ys[1000];

		std::vector<float> x_points;
		std::vector<float> y_points;

		float tan_xs[1000];
		float tan_ys[1000];

		//float x_calc = 0;

		float gen_angle = 3.14f / 2.f;
		float z_offset = 0.f;
		float stretch = 50.f;

		bool show_process = false;

		float move_point = 0.f;

	};

}
