#include "StateBase.h"


#include "Input.h"
#include "Shapes.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "implot.h"



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
		lightCube.scale = glm::vec3(0.4f);

		lineOb.color = glm::vec3(1.0f, 1.0f, 1.0f);
		lineOb.position = glm::vec3(1.f, 1.f, 1.f);
		lineOb.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		lineOb.scale = glm::vec3(1.0f);

		line_start = glm::vec3(0.0f, 0.0f, 0.0f);
		line_end = glm::vec3(1.f, 1.f, 1.f);

		gravity = 9.8f;
		velocity = 10.f;
		angle = 3.14f / 4.f;

		point_pos = glm::vec3(5.f, 5.f, 0.f);

		yes_col = glm::vec3(0.f, 0.7f, 0.3f);
		no_col = glm::vec3(0.86f, 0.1f, 0.13f);

		point_col = glm::vec3(1.f, 1.f, 1.f);

		plat_col = glm::vec3(1.f, 0.58f, 0.04f);
		//start_col = glm::vec3(0.98f, 0.96f, 0.19f);
		start_col = glm::vec3(0.6f, 0.79f, 0.24f);
		end_col = glm::vec3(0.98f, 0.17f, 0.2f);
		hyper_col = glm::vec3(0.28f, 0.62f, 0.81f);

		closest_point_pos = line_start;
		point_offset = line_start;


		//reset gameplay graph
		grammar.reset_graph();

		//perform all trasformations
		grammar.GenerateWholeGraph(window);

		//generate random game space
		Graph gameplay_graph = grammar.get_output_graph();
		phys.construct_graph(gameplay_graph);

		//resolve all constraints
		phys.resolve_all_constraints();


	}

	void StateBase::frame(float dt, GLFWwindow* window, Input* in)
	{

		frameTime = 1.f / dt;

		// handle inputs
		processInput(dt, window, in);


		// update stuff




		//render guys
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearColor(0.118f, 0.118f, 0.118f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (wireFrameToggle) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
		else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

		//projection and view matrices
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1440.0f / 960.0f, 0.1f, 300.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);


		//Cube object

		model = glm::mat4(1.0f);
		model = glm::translate(model, cube.position);
		model = glm::scale(model, cube.scale);

		//shaders.litShader.UseShader(model, view, projection, cube.color, light.color, light.position, camera.Position);
		//Geometry::DrawVArray(cubeVN);


		// light object
		/*
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightCube.position);
		model = glm::scale(model, lightCube.scale);

		shaders.flatShader.UseShader(model, view, projection, light.color);
		Geometry::DrawVArray(cubeV);*/


		/*
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
		}*/

		//ImGui::Checkbox("show process", &show_process);
		//ImGui::Checkbox("show lines", &show_lines);
		/*
		if (ImGui::Checkbox("show constraints", &show_constraints))
		{

			phys.color_graph();

		}*/
		//ImGui::Checkbox("update physics every frame", &physics_updates);

		//ImGui::SliderFloat("particle speed", &speed, 0.f, 10.f);

		if (physics_updates)
		{
			//phys.update(dt);
			phys.particle_update(speed, dt);
		}

		if (!show_process)
		{
			
			
			draw_space_graph();
			/*
			ImGui::SliderFloat("gen angle", &gen_angle, 0.f, 3.14f);
			ImGui::SliderFloat("z wobble", &z_offset, -50.f, 50.f);
			ImGui::SliderFloat("stretch factor", &stretch, 10.f, 100.f);



			if (ImGui::Button("build level from grammar graph"))
			{
				Graph gameplay_graph = grammar.get_output_graph();
				phys.construct_graph(gameplay_graph);
				//phys.color_graph();
			}
			if (ImGui::Button("make level"))
			{
				glm::vec3 dir = glm::vec3(sinf(gen_angle), -cosf(gen_angle), 0.f);
				phys.make_test_graph(dir, z_offset, stretch);
				//phys.make_test_graph_branch(dir, z_offset, stretch);
			}
			if (ImGui::Button("make branch level"))
			{
				glm::vec3 dir = glm::vec3(sinf(gen_angle), -cosf(gen_angle), 0.f);
				//phys.make_test_graph(dir, z_offset, stretch);
				phys.make_test_graph_branch(dir, z_offset, stretch);
			}
			if (ImGui::Button("make big branch level"))
			{
				glm::vec3 dir = glm::vec3(sinf(gen_angle), -cosf(gen_angle), 0.f);
				//phys.make_test_graph(dir, z_offset, stretch);
				phys.make_test_graph_big_branch(dir, z_offset, stretch);
			}
			if (ImGui::Button("resolve constraints"))
			{
				phys.resolve_constraints();
				phys.color_graph();
			} */
			/*
			ImGui::SliderFloat("move pos", &move_point, -100.f, 100.f);
			if (ImGui::Button("move"))
			{
				bool stop = false;
				for (int i = 0; i < phys.space_graph.size(); i++)
				{
					if (phys.space_graph[i].constraints.size() > 0)
					{
						for (const Constraint& c : phys.space_graph[i].constraints)
						{

							//check if already within trajectory
							if (!Physics::trajectory_test(c.t_info, phys.space_graph[c.index].position, phys.space_graph[i].position))
							{
																
								phys.space_graph[i].position.y = move_point;
								
								stop = true;
								break;


							}



						}
					}
					if (stop)
					{
						break;
					}
				}
			}*/
		}
		else
		{
			DrawTrajectoryDemo();
		}


		glBindVertexArray(0);



		gui(window);

		/*
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

		}*/


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

	void StateBase::gui(GLFWwindow* window)
	{


		ImGui::Separator();
		ImGui::Text("HOLD RIGHT MOUSE BUTTON AND MOVE MOUSE TO LOOK AROUND");
		ImGui::Text("PRESS WASD KEYS TO MOVE AROUND");
		ImGui::Separator();
		ImGui::Text("FPS: %.2f", frameTime);
		//ImGui::Checkbox("debug", &debugBool);
		//ImGui::Checkbox("Wireframe Mode", &wireFrameToggle);

		/*
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


			//trajectory
			ImGui::SliderFloat("velocity", &velocity, 5, 50);
			ImGui::SliderFloat("angle", &angle, 3.14f / -2.f, 3.14f / 2.f);
			ImGui::SliderFloat("gravity", &gravity, 5, 15);


			float point[3] = { point_pos.x, point_pos.y, point_pos.z };
			ImGui::SliderFloat("point position x", point, -30, 30);
			ImGui::SliderFloat("point position y", &point[1], -50, 20);
			ImGui::SliderFloat("point position z", &point[2], -30, 30);
			point_pos.x = point[0];
			point_pos.y = point[1];
			point_pos.z = point[2];

			float off[3] = { point_offset.x, point_offset.y, point_offset.z };
			ImGui::SliderFloat("point offset x", off, 0, 50);
			ImGui::SliderFloat("point offset y", &off[1], -50, 20);
			ImGui::SliderFloat("point offset z", &off[2], -30, 30);
			point_offset.x = off[0];
			point_offset.y = off[1];
			point_offset.z = off[2];

			//angle, magnitude, height controls
			point_angle = Physics::get_angle_between_vectors2(glm::vec2(1, 0), glm::vec2(point_pos.x, point_pos.z));
			glm::vec2 pr(point_pos.x, point_pos.z);
			point_mag = glm::length(pr);
			point_height = point_pos.y;


			ImGui::Checkbox("Show Trajectory Rotations", &show_rotations);
			ImGui::SliderInt("number of rotations", &traj_its, 15, 100);

		}



		//draw graphs
		if (ImGui::CollapsingHeader("graphs"))
		{
			ShowGraphs();
		}*/

		ShowMainControls(window);
		ShowDataCollectionControls();
		ShowTrajectoryDemoControls();

		ShowExampleLevelControls();
		

	}

	void StateBase::draw_space_graph()
	{




		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1440.0f / 960.0f, 0.1f, 300.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);


		phys.color_graph();

		for (SpaceNode sn : phys.space_graph)
		{

			if (sn.name == "start")
			{
				sn.color = start_col;
			}
			if (sn.name == "end")
			{
				sn.color = end_col;
			}
			if (sn.is_hyper)
			{
				sn.color = hyper_col;
			}


			//draw platform
			model = glm::mat4(1.0f);
			model = glm::translate(model, sn.position);
			model = glm::scale(model, lightCube.scale);

			shaders.flatShader.UseShader(model, view, projection, sn.color);
			Geometry::DrawVArray(cubeV);
			

			//draw each attached constraint (from previous platform)
			if (sn.constraints.size() > 0)
			{
				for (Constraint& c : sn.constraints)
				{
					glm::vec3 line_col = glm::vec3(1.f, 1.f, 1.f);
					
					if (c.is_hyper)
					{
						line_col = hyper_col;
					}

					if (show_lines)
					{
						// draw line
						model = glm::mat4(1.0f);
						shaders.lineShader.UseShader(sn.position, phys.space_graph[c.index].position, model, view, projection, line_col);
						Geometry::DrawVArrayLine(line);
					}
					if (show_constraints && !c.is_hyper)
					{


						glm::vec3 t_col = yes_col;

						if (Physics::trajectory_test(c.t_info, phys.space_graph[c.index].position, sn.position))
						{
							//point_col = yes_col;
						}
						else
						{
							//point_col = no_col;
						}


						glm::vec3 diff = sn.position - phys.space_graph[c.index].position;

						//calculate angle between point and trajectory
						float ang = Physics::get_angle_between_vectors2(glm::vec2(1, 0), glm::vec2(diff.x, diff.z));


						//draw trajectory
						model = glm::mat4(1.0f);
						model = glm::translate(model, phys.space_graph[c.index].position);
						model = glm::rotate(model, ang, glm::vec3(0, 1, 0));
						shaders.trajShader.UseShader(c.t_info.gravity, c.t_info.angle, c.t_info.velocity, model, view, projection, c.color);
						Geometry::DrawVArrayLineStrip(trajectory);


						/*
						//draw trajectory
						model = glm::mat4(1.0f);
						model = glm::translate(model, phys.space_graph[1].position);
						model = glm::rotate(model, ang, glm::vec3(0, 1, 0));
						shaders.trajShader.UseShader(c.t_info.gravity, c.t_info.angle, c.t_info.velocity, model, view, projection, lineOb.color);
						Geometry::DrawVArrayLineStrip(trajectory);
						*/

					}
				}

			}




		}















	}

	void StateBase::DrawLevel()
	{
	}

	void StateBase::DrawTrajectoryDemo()
	{

		//projection and view matrices
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1440.0f / 960.0f, 0.1f, 300.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);


		glm::vec3 t_orig = point_offset;
		glm::vec3 t_point = point_offset + point_pos;



		// draw line
		model = glm::mat4(1.0f);
		//model = glm::translate(model, t_orig);
		//shaders.lineShader.UseShader(t_orig, t_point, model, view, projection, lineOb.color);
		//Geometry::DrawVArrayLine(line);


		//calculate angle between point and trajectory

		point_angle = Physics::get_angle_between_vectors2(glm::vec2(1, 0), glm::vec2(t_point.x, t_point.z));


		//draw trajectory
		model = glm::mat4(1.0f);
		model = glm::translate(model, t_orig);
		model = glm::rotate(model, point_angle, glm::vec3(0, 1, 0));
		shaders.trajShader.UseShader(gravity, angle, velocity, model, view, projection, point_col);
		Geometry::DrawVArrayLineStrip(trajectory);



		if (Physics::trajectory_test(velocity, gravity, angle, t_orig, t_point))
		{
			point_col = yes_col;
		}
		else
		{
			point_col = no_col;
		}


		//draw point
		model = glm::mat4(1.0f);
		model = glm::translate(model, t_point);
		model = glm::scale(model, lightCube.scale);

		shaders.flatShader.UseShader(model, view, projection, plat_col);
		Geometry::DrawVArray(cubeV);

		//draw platform
		model = glm::mat4(1.0f);
		model = glm::translate(model, t_orig);
		model = glm::scale(model, lightCube.scale);

		shaders.flatShader.UseShader(model, view, projection, plat_col);
		Geometry::DrawVArray(cubeV);



		//calculate closest point
		/*
		if (ImGui::Checkbox("Calculate Closest Point every frame", &calc_closest_point))
		{
			//closest_point_pos = Physics::get_closest_point(velocity, gravity, angle, line_start, point_pos);
		}
		if (ImGui::Button("Calculate Closest Point now") || calc_closest_point)
		{
		}*/
		
		closest_point_pos = Physics::get_closest_point(velocity, gravity, angle, t_orig, t_point);


		//draw effective x
		/*
		glm::vec3 proj_point = point_pos - line_start;
		proj_point.y = 0.f;

		model = glm::mat4(1.0f);
		shaders.lineShader.UseShader(line_start, proj_point, model, view, projection, lineOb.color);
		Geometry::DrawVArrayLine(line);*/

		//draw closest point
		model = glm::mat4(1.0f);
		model = glm::translate(model, closest_point_pos);
		model = glm::scale(model, lightCube.scale);

		shaders.flatShader.UseShader(model, view, projection, lineOb.color);
		Geometry::DrawVArray(cubeV);


		model = glm::mat4(1.0f);
		shaders.lineShader.UseShader(closest_point_pos, t_point, model, view, projection, lineOb.color);
		Geometry::DrawVArrayLine(line);


		//draw copy of trajectory rotated around platform


		if (show_rotations)
		{
			for (int i = 1; i < traj_its; i++)
			{

				float full_angle = 2 * 3.14f;
				float part_angle = point_angle + (full_angle / (float)traj_its) * i;

				model = glm::mat4(1.0f);
				model = glm::translate(model, t_orig);
				model = glm::rotate(model, part_angle, glm::vec3(0.f, 1.0f, 0.f));


				shaders.trajShader.UseShader(gravity, angle, velocity, model, view, projection, lineOb.color);
				Geometry::DrawVArrayLineStrip(trajectory);

			}
		}
	}

	void StateBase::ShowMainControls(GLFWwindow* window)
	{

		if (ImGui::Button("Generate New Level"))
		{
			//reset gameplay graph
			grammar.reset_graph();

			//perform all trasformations
			grammar.GenerateWholeGraph(window);

			//generate random game space
			Graph gameplay_graph = grammar.get_output_graph();
			phys.construct_graph(gameplay_graph);

			//resolve all constraints
			phys.resolve_all_constraints();

		}

		ImGui::Separator();

		// Gameplay commands

		if (ImGui::Button("Generate New Gameplay Graph"))
		{
			// reset gameplay graph
			grammar.reset_graph();

			//preform all transformations
			grammar.GenerateWholeGraph(window);

			// generate random game space
			Graph gameplay_graph = grammar.get_output_graph();
			phys.construct_graph(gameplay_graph);

		}
		if (ImGui::Button("Reset Gameplay Graph"))
		{
			//reset gameplay graph
			grammar.reset_graph();

			//generate random game space
			Graph gameplay_graph = grammar.get_output_graph();
			phys.construct_graph(gameplay_graph);

		}
		if (ImGui::Button("Do Single Graph Transformation"))
		{
			//perform single grammar tf
			grammar.generate_graph(window);

			// generate random game space
			Graph gameplay_graph = grammar.get_output_graph();
			phys.construct_graph(gameplay_graph);
		}

		ImGui::Separator();

		// Game Space commands

		if (ImGui::Button("Generate New Game Space"))
		{
			//generate random game space from grammar graph
			Graph gameplay_graph = grammar.get_output_graph();
			phys.construct_graph(gameplay_graph);

			// resolve all constraints
			phys.resolve_all_constraints();


		}
		if (ImGui::Button("Reset Game Space"))
		{
			//generate random game space from grammar graph
			Graph gameplay_graph = grammar.get_output_graph();
			phys.construct_graph(gameplay_graph);


		}
		if (ImGui::Button("Resolve All Constraints"))
		{
			//resolve a single constraint
			phys.resolve_all_constraints();
			phys.color_graph();

		}
		if (ImGui::Button("Do Single Constraint Resolution"))
		{
			//resolve a single constraint
			phys.resolve_constraints();
			phys.color_graph();

		}

		ImGui::SeparatorText("Display Settings");

		ImGui::Checkbox("show lines", &show_lines);
		ImGui::Checkbox("show constraints", &show_constraints);


	}

	void StateBase::ShowTrajectoryDemoControls()
	{

		if (ImGui::CollapsingHeader("Trajectory Demo"))
		{

			ImGui::Checkbox("Show Trajectory Demo", &show_process);

			ImGui::Checkbox("Show Trajectory Rotations", &show_rotations);

			ImGui::SeparatorText("Trajectory Parameters");

			//trajectory
			ImGui::SliderFloat("Velocity", &velocity, 5, 50);
			ImGui::SliderFloat("Angle", &angle, 3.14f / -2.f, 3.14f / 2.f);
			ImGui::SliderFloat("Gravity", &gravity, 5, 15);

			ImGui::SeparatorText("Point Position");

			float point[3] = { point_pos.x, point_pos.y, point_pos.z };
			ImGui::SliderFloat("x", point, -50, 50);
			ImGui::SliderFloat("y", &point[1], -150, 30);
			ImGui::SliderFloat("z", &point[2], -50, 50);
			point_pos.x = point[0];
			point_pos.y = point[1];
			point_pos.z = point[2];

			ImGui::SeparatorText("Trajectory offset");

			float off[3] = { point_offset.x, point_offset.y, point_offset.z };
			ImGui::SliderFloat("offset x", off, 0, 50);
			ImGui::SliderFloat("offset y", &off[1], -50, 20);
			ImGui::SliderFloat("offset z", &off[2], -30, 30);
			point_offset.x = off[0];
			point_offset.y = off[1];
			point_offset.z = off[2];

			//angle, magnitude, height controls
			point_angle = Physics::get_angle_between_vectors2(glm::vec2(1, 0), glm::vec2(point_pos.x, point_pos.z));
			glm::vec2 pr(point_pos.x, point_pos.z);
			point_mag = glm::length(pr);
			point_height = point_pos.y;
					

			ShowGraphs();

		}
	}

	void StateBase::ShowExampleLevelControls()
	{
		if (ImGui::CollapsingHeader("Other Game Space Controls"))
		{

			ImGui::Checkbox("update physics every frame", &physics_updates);
			ImGui::Separator();

			ImGui::SliderFloat("Generation Angle", &gen_angle, 0.f, 3.14f);
			ImGui::SliderFloat("z-Axis Wobble", &z_offset, -50.f, 50.f);
			ImGui::SliderFloat("Stretch Factor", &stretch, 10.f, 100.f);



			if (ImGui::Button("Build Level From Grammar Graph"))
			{
				Graph gameplay_graph = grammar.get_output_graph();
				phys.construct_graph(gameplay_graph);
				//phys.color_graph();
			}
			if (ImGui::Button("Make Simple Level"))
			{
				glm::vec3 dir = glm::vec3(sinf(gen_angle), -cosf(gen_angle), 0.f);
				phys.make_test_graph(dir, z_offset, stretch);
				//phys.make_test_graph_branch(dir, z_offset, stretch);
			}
			if (ImGui::Button("Make Test Branch Level"))
			{
				glm::vec3 dir = glm::vec3(sinf(gen_angle), -cosf(gen_angle), 0.f);
				//phys.make_test_graph(dir, z_offset, stretch);
				phys.make_test_graph_branch(dir, z_offset, stretch);
			}
			if (ImGui::Button("Make Big Test Branch Level"))
			{
				glm::vec3 dir = glm::vec3(sinf(gen_angle), -cosf(gen_angle), 0.f);
				//phys.make_test_graph(dir, z_offset, stretch);
				phys.make_test_graph_big_branch(dir, z_offset, stretch);
			}
			if (ImGui::Button("Resolve a Single Constraint"))
			{
				phys.resolve_constraints();
				phys.color_graph();
			}
		}
	}

	void StateBase::ShowDataCollectionControls()
	{

		if (ImGui::CollapsingHeader("Data Collection"))
		{

			if (ImGui::Button("Collect Data"))
			{

			}


		}


	}

	void StateBase::ShowGraphs()
	{

		glm::vec2 pr(point_pos.x, point_pos.z);
		point_mag = glm::length(pr);
		float mag = glm::length(pr);

		/*
		//ImGui::SliderFloat("Show calculation", &x_calc, 0, 100);
		float r = 0;

		if (ImGui::Button("show maths"))
		{
			float a = mag;
			float b = point_pos.y;

			float c = tanf(angle);

			float d = gravity / (2 * velocity * velocity * cosf(angle) * cosf(angle));

			float tx = x_calc;
			float ty = (tx * c) - (tx * tx * d);

			float d2x = (powf(d, 2) * powf(tx, 4)) - (2 * c * d * powf(tx, 3)) + ((1 + c + (2 * b * d)) * powf(tx, 2)) + ((-2 * a - (2 * c * b)) * tx) + powf(a, 2) + powf(b, 2);
			r = d2x;

			float dpx = (4 * powf(d, 2) * powf(tx, 3)) - (6 * c * d * powf(tx, 2)) + ((2 + (2 * c) + (4 * b * d)) * tx) + ((-2 * a) - (2 * c * b));
			//r = dpx; 


			float cosa = cosf(angle);
			float y = tx * (tanf(angle) - (tx * (gravity / (2 * velocity * velocity * cosa * cosa))));

			std::cout << "point: (" << a << ", ";
			std::cout << b << ")\n";
			std::cout << "gravity: " << gravity << ", velocity: " << velocity << ", angle: " << angle;
			std::cout << "c = " << c << ",  d = " << d;
			std::cout << "\ntrajectory: (" << tx << ", " << ty << ")\n";
			std::cout << "alt trajectory: (" << tx << ", " << y << ")\n";
			std::cout << "dist sq: " << d2x << ", dist: " << sqrtf(d2x) << "\n";
			glm::vec2 ta(tx, ty); glm::vec2 tb(a, b);
			glm::vec2 tr = tb - ta;
			std::cout << "calc distance: " << glm::length(tr);
			std::cout << "\ngradient: " << dpx;

		}*/


		//ImGui::SliderFloat("result: ", &r, -100, 100);

		//fill graph data


		x_points.clear();
		y_points.clear();

		for (int i = 0; i < 1000; i++)
		{


			float c = tanf(angle);

			float d = gravity / (2 * velocity * velocity * cosf(angle) * cosf(angle));


			traj_xs[i] = i * 0.1f;

			//traj_ys[i] = traj_xs[i] * (tanf(angle) - (traj_xs[i] * (gravity / (2.f * velocity * velocity * cosf(angle) * cosf(angle)))));
			traj_ys[i] = (traj_xs[i] * c) - (traj_xs[i] * traj_xs[i] * d);

			float tx = traj_xs[i];

			float a = mag;
			float b = point_pos.y;

			dist_xs[i] = traj_xs[i];
			dist_ys[i] = (powf(d, 2) * powf(tx, 4)) - (2 * c * d * powf(tx, 3)) + ((1 + powf(c, 2) + (2 * b * d)) * powf(tx, 2)) + ((-2 * a - (2 * c * b)) * tx) + powf(a, 2) + powf(b, 2);

			dist_root_xs[i] = tx;
			dist_root_ys[i] = sqrtf(dist_ys[i]);

			der_xs[i] = tx;
			der_ys[i] = (4 * powf(d, 2) * powf(tx, 3)) - (6 * c * d * powf(tx, 2)) + ((1 + powf(c, 2) + (2 * b * d)) * 2 * tx) + ((-2 * a) - (2 * c * b));

			if (der_ys[i] >= -0.3f && der_ys[i] <= 0.3f)
			{
				//x_points.push_back(der_xs[i]);
				//y_points.push_back(der_ys[i]);

				x_points.push_back(der_xs[i]);
				y_points.push_back(traj_ys[i]);

				x_points.push_back(a);
				y_points.push_back(b);


			}

			tan_xs[i] = tx;
			tan_ys[i] = d;

		}






		if (ImPlot::BeginPlot("Test Plot"))
		{

			ImPlot::PlotLine("Trajectory", traj_xs, traj_ys, 1000);

			ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);

			ImPlot::PlotLine("Point", &mag, &point_pos.y, 1);

			ImPlot::PlotLine("Distance Squared", dist_xs, dist_ys, 1000);
			ImPlot::PlotLine("Distance", dist_root_xs, dist_root_ys, 1000);
			//ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
			ImPlot::PlotLine("Derivative of Distance Squared", der_xs, der_ys, 1000);

			//ImPlot::SetNextLineStyle(ImPlotLineFlags_None)
			ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
			ImPlot::PlotLine("Closest Points", x_points.data(), y_points.data(), x_points.size(), ImPlotLineFlags_Segments);


			ImPlot::PlotLine("tan(angle)", tan_xs, tan_ys, 1000);

			ImPlot::EndPlot();
		}




	}

}