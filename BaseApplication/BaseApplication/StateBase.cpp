#include "StateBase.h"


#include "Input.h"
#include "Shapes.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


namespace Hollow {







	StateBase::StateBase()
	{
		//shaders = new Shaders();

	}

	StateBase::~StateBase()
	{
	}

	void StateBase::Init(GLFWwindow* window)
	{

		Shape* shapeptr = new Cube();

		cubeVN = Geometry::SetupVAO(shapeptr);
		cubeV = Geometry::SetupVAO(shapeptr, cubeVN.VBO);

		delete shapeptr;
		shapeptr = nullptr;

		Shape* lineptr = new Line();
		line = Geometry::SetupVAO(lineptr);
		delete lineptr;
		lineptr = nullptr;

		Shape* trajptr = new Trajectory();
		trajectory = Geometry::SetupVAO(trajptr);
		delete trajptr;
		trajptr = nullptr;


		cube.color = glm::vec3(1.0f, 0.5f, 0.31f);
		cube.position = glm::vec3(-3.0f, 3.0f, 0.0f);
		cube.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		cube.scale = glm::vec3(1.0f);

		light.color = glm::vec3(1.0f, 1.0f, 1.0f);
		light.position = glm::vec3(1.2f, 1.0f, 2.0f);

		lightCube.color = light.color;
		lightCube.position = light.position;
		lightCube.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		lightCube.scale = glm::vec3(0.2f);

		lineOb.color = glm::vec3(1.0f, 1.0f, 1.0f);
		lineOb.position = glm::vec3(1.f, 1.f, 1.f);
		lineOb.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		lineOb.scale = glm::vec3(1.0f);

		line_start = glm::vec3(0.0f, 0.0f, 0.0f);
		line_end = glm::vec3(1.f, 1.f, 1.f);

		gravity = 9.8f;
		velocity = 10.f;
		angle = 3.14f / 4.f;

	}

	void StateBase::frame(float dt, GLFWwindow* window, Input* in)
	{

		frameTime = 1.f / dt;

		// handle inputs
		processInput(dt, window, in);


		// update stuff




		//render guys
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (wireFrameToggle) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
		else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

		//projection and view matrices
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1440.0f / 960.0f, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);


		//Cube object

		model = glm::mat4(1.0f);
		model = glm::translate(model, cube.position);
		model = glm::scale(model, cube.scale);

		shaders.litShader.UseShader(model, view, projection, cube.color, light.color, light.position, camera.Position);
		Geometry::DrawVArray(cubeVN);


		// light object

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightCube.position);
		model = glm::scale(model, lightCube.scale);

		shaders.flatShader.UseShader(model, view, projection, light.color);
		Geometry::DrawVArray(cubeV);



		glm::vec3 cubePositions[] = {
			glm::vec3(3.0f,  3.0f,  3.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);

			shaders.litShader.UseShader(model, view, projection, cube.color, light.color, light.position, camera.Position);
			Geometry::DrawVArray(cubeVN);
		}

		// draw line
		model = glm::mat4(1.0f);
		shaders.lineShader.UseShader(line_start, line_end, model, view, projection, lineOb.color);
		Geometry::DrawVArrayLine(line);

		//draw trajectory
		model = glm::mat4(1.0f);
		shaders.trajShader.UseShader(gravity, angle, velocity, model, view, projection, lineOb.color);
		Geometry::DrawVArrayLineStrip(trajectory);


		glBindVertexArray(0);



		gui();

		if (ImGui::CollapsingHeader("Grammar"))
		{
			grammar.generate_graph(window);

			if (ImGui::Button("Copy Current Level Graph to Clipboard"))
			{
				grammar.copy_current_graph(window);
			}

			if (ImGui::Button("Reset Graph"))
			{
				grammar.reset_graph();
			}

		}


	}

	void StateBase::processInput(float dt, GLFWwindow* window, Input* in)
	{

		float speed = 1.f;

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		Camera_Movement mov = FORWARD;
		bool move = false;

		if (in->isKeyDown(Input::KEYS::W))
		{
			mov = FORWARD;
			move = true;
		}
		if (in->isKeyDown(Input::KEYS::S))
		{
			mov = BACKWARD;
			move = true;
		}

		if (in->isKeyDown(Input::KEYS::D))
		{
			mov = RIGHT;
			move = true;
		}
		if (in->isKeyDown(Input::KEYS::A))
		{
			mov = LEFT;
			move = true;
		}

		if (move)
		{
			camera.ProcessKeyboard(mov, dt);
		}

		if (in->firstMouse)
		{
			in->lastmousex = in->mousex;
			in->lastmousey = in->mousey;
			in->firstMouse = false;
		}


		float xoffset = in->mousex - in->lastmousex;
		float yoffset = in->lastmousey - in->mousey;
		in->lastmousex = in->mousex;
		in->lastmousey = in->mousey;
		/*
			const float sensitivity = 0.04f;
			xoffset *= sensitivity;
			yoffset *= sensitivity;

			cam.yaw += xoffset;
			cam.pitch += yoffset;

			if (cam.pitch > 89.0f) { cam.pitch = 89.0f; }
			if (cam.pitch < -89.0f) { cam.pitch = -89.0f; }

			cam.calculateDirectionFromAngles();
		*/
		if (in->mouseCaptured)
		{
			camera.ProcessMouseMovement(xoffset, yoffset);
		}

	}


	void StateBase::Cleanup()
	{


	}

	void StateBase::gui()
	{


		ImGui::Separator();
		ImGui::Text("HOLD RIGHT MOUSE BUTTON AND MOVE MOUSE TO LOOK AROUND");
		ImGui::Text("PRESS WASD KEYS TO MOVE AROUND");
		ImGui::Separator();
		ImGui::Text("FPS: %.2f", frameTime);
		//ImGui::Checkbox("debug", &debugBool);
		ImGui::Checkbox("Wireframe Mode", &wireFrameToggle);

		if (ImGui::CollapsingHeader("Graphics"))
		{

			float cols[3] = { light.color.r, light.color.g, light.color.b };
			ImGui::ColorPicker3("Light Color", cols);
			light.color.r = cols[0];
			light.color.g = cols[1];
			light.color.b = cols[2];
		}

		if (ImGui::CollapsingHeader("Physics"))
		{

			//line 
			float line_s[3] = { line_start.x, line_start.y, line_start.z };
			ImGui::SliderFloat3("line start", line_s, -10, 10);
			line_start.x = line_s[0];
			line_start.y = line_s[1];
			line_start.z = line_s[2];

			float line_e[3] = { line_end.x, line_end.y, line_end.z };
			ImGui::SliderFloat3("line end", line_e, -10, 10);
			line_end.x = line_e[0];
			line_end.y = line_e[1];
			line_end.z = line_e[2];


			//trajectory
			ImGui::SliderFloat("velocity", &velocity, 0, 10);
			ImGui::SliderFloat("angle", &angle, 0, 3.14f / 2.f);
			ImGui::SliderFloat("gravity", &gravity, 5, 15);


		}



	}

}