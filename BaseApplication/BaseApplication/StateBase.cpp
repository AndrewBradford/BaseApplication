#include "StateBase.h"


#include "Input.h"
#include "Shapes.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



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


		cube.color = glm::vec3(1.0f, 0.5f, 0.31f);
		cube.position = glm::vec3(0.0f, 0.0f, 0.0f);
		cube.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		cube.scale = glm::vec3(1.0f);

		light.color = glm::vec3(1.0f, 1.0f, 1.0f);
		light.position = glm::vec3(1.2f, 1.0f, 2.0f);

		lightCube.color = light.color;
		lightCube.position = light.position;
		lightCube.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		lightCube.scale = glm::vec3(0.2f);



	}

	void StateBase::frame(float dt, GLFWwindow* window, Input* in)
	{


		// handle inputs
		processInput(dt, window, in);


		// update stuff




		//render guys
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//projection and view matrices
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
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

		shaders.flatShader.UseShader(model, view, projection);
		Geometry::DrawVArray(cubeV);



		glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
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
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));


			shaders.litShader.UseShader(model, view, projection, cube.color, light.color, light.position, camera.Position);
			Geometry::DrawVArray(cubeVN);


		}

		glBindVertexArray(0);



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

		camera.ProcessMouseMovement(xoffset, yoffset);


	}


	void StateBase::Cleanup()
	{


	}

}