#pragma once


#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "HyperEdgeGrammar.h"
#include <ctime>


struct TrajectoryInfo {

	float angle = 3.14f / 4.f;
	float velocity = 10.0f;
	float gravity = 9.8f;
};

struct Constraint {

	TrajectoryInfo t_info;
	int index = 0;

	bool is_satisfied = false;
	//bool is_solid = true;
	glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
	bool is_hyper = false;

};

struct SpaceNode {

	std::string name;
	glm::vec3 position;
	std::vector<Constraint> constraints;


	glm::vec3 velocity = glm::vec3(0.f, 0.f, 0.f);
	
	bool is_hyper = false;

	bool is_solid = true;

	glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
};

class Physics
{

public:

	static bool trajectory_test(float velocity, float gravity, float angle, glm::vec3 origin, glm::vec3 point)
	{
		// calculate distance vector and project onto xz plane
		glm::vec3 proj = point - origin;
		proj.y = 0.f;

		
		float point_x = glm::length(proj);
		float point_y = (point - origin).y;

		float cosa = cosf(angle);
		float traj_y = point_x * (tanf(angle) - (point_x * (gravity / (2 * velocity * velocity * cosa * cosa))));

		if (traj_y >= point_y)
		{
			return true;
		}
		else
		{
			return false;
		}


	}

	static bool trajectory_test(TrajectoryInfo t, glm::vec3 origin, glm::vec3 point)
	{
		return trajectory_test(t.velocity, t.gravity, t.angle, origin, point);
	}


	static float get_angle_between_vectors2(glm::vec2 a, glm::vec2 b)
	{
		float c = -1;
		if (b.y < 0) { c = 1; }
		return c * acosf(glm::dot(a, b) / (glm::length(a) * glm::length(b)));

	}


	static float get_y_at_x(float velocity, float gravity, float angle, float x)
	{

		float cosa = cosf(angle);
		return x * (tanf(angle) - (x * (gravity / (2 * velocity * velocity * cosa * cosa))));

	}

	static float get_y_at_x(TrajectoryInfo t, float x)
	{
		return get_y_at_x(t.velocity, t.gravity, t.angle, x);
	}


	static glm::vec3 get_closest_point(float velocity, float gravity, float angle, glm::vec3 origin, glm::vec3 point)
	{


		glm::vec3 proj = point - origin;
		proj.y = 0.f;


		float point_x = glm::length(proj);
		float point_y = (point - origin).y;


		float a = point_x;
		float b = point_y;

		float c = tanf(angle);

		float d = gravity / (2 * velocity * velocity * cosf(angle) * cosf(angle));

		float closest_val = 1000000.f;
		float closest_x = 0;

		for (int i = 10; i < 1000; i++)
		{


			float tx = float(i) * (100.f/1000.f);
			float ty = (tx * c) - (tx * tx * d);

			float d2x = (powf(d, 2) * powf(tx, 4)) - (2 * c * d * powf(tx, 3)) + ((1 + powf(c, 2) + (2 * b * d)) * powf(tx, 2)) + ((-2 * a - (2 * c * b)) * tx) + powf(a, 2) + powf(b, 2);

			if (d2x <= closest_val)
			{
				closest_val = d2x;
				closest_x = tx;
			}

		}


		float closest_y = get_y_at_x(velocity, gravity, angle, closest_x);
		proj = glm::normalize(proj);
		proj *= closest_x;


		glm::vec3 closest_point(proj.x, closest_y, proj.z);

		return closest_point + origin;



	}

	glm::vec3 get_closest_point(TrajectoryInfo t, glm::vec3 origin, glm::vec3 point)
	{
		return get_closest_point(t.velocity, t.gravity, t.angle, origin, point);
	}

	glm::vec3 get_closest_crossover_point(TrajectoryInfo t1, TrajectoryInfo t2, glm::vec3 origin, glm::vec3 point1, glm::vec3 point2)
	{
		glm::vec3 sol = glm::vec3(0, 0, 0);

		return sol;
	}

	Physics()
	{
		build_constraint_map();
		make_test_graph(glm::vec3(1, 0, 0), 0.f, 50.f);
		//make_test_graph_branch(glm::vec3(1, 0, 0), 0.f, 50.f);
		std::srand(std::time(0));
	}

	~Physics()
	{

	}

	//void add_Node(Constraint c, int )

	void make_test_graph(glm::vec3 dir, float z_offset, float stretch)
	{

		space_graph.clear();

		int node = 0;

		float dist = 50.f;
		dist = stretch;

		// start, 0
		SpaceNode sn;
		sn.name = "start";
		sn.position = glm::vec3(0, 0, 0);
		sn.color = glm::vec3(1.f, 0.58f, 0.04f);
		sn.is_solid = true;
		
		
		space_graph.push_back(sn);

		node++;

		// 1
		sn.name = "first mid";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		Constraint c;
		c.index = 0;
		c.t_info = constraint_map[EdgeLabel::dive_spring];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);


		node++;


		/*
		sn.name = "branch mid";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = z_offset;
		sn.is_solid = true;
		sn.constraints.clear();

		//Constraint c;
		c.index = 1;
		c.t_info = constraint_map[EdgeLabel::long_jump];
		sn.constraints.push_back(c);

		//space_graph.push_back(sn);


		node++;*/

		// 2
		sn.name = "mid";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 1;
		c.t_info = constraint_map[EdgeLabel::jump];
		sn.constraints.push_back(c);

		/*
		c.index = 2;
		c.t_info = constraint_map[EdgeLabel::dive_spring];
		sn.constraints.push_back(c);*/

		space_graph.push_back(sn);


		node++;

		// end, 3

		sn.name = "end";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();
				
		c.index = 2;
		c.t_info = constraint_map[EdgeLabel::long_jump];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);


		color_graph();

	}

	void make_test_graph_branch(glm::vec3 dir, float z_offset, float stretch)
	{

		space_graph.clear();

		int node = 0;

		Constraint c;
		float dist = 50.f;
		dist = stretch;

		// start, 0
		SpaceNode sn;
		sn.name = "start";
		sn.position = glm::vec3(0, 0, 0);
		sn.color = glm::vec3(1.f, 0.58f, 0.04f);
		sn.is_solid = true;


		space_graph.push_back(sn);

		node++;

		// 1
		sn.name = "first mid";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 0;
		c.t_info = constraint_map[EdgeLabel::dive_spring];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);


		//node++;


		//2
		sn.name = "branch mid";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 0;
		c.t_info = constraint_map[EdgeLabel::long_jump];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);


		node++;

		// 3
		sn.name = "mid";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 1;
		c.t_info = constraint_map[EdgeLabel::dive];
		sn.constraints.push_back(c);

		
		c.index = 2;
		c.t_info = constraint_map[EdgeLabel::dive_spring];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);


		node++;

		// end, 4

		sn.name = "end";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 3;
		c.t_info = constraint_map[EdgeLabel::long_jump];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);


		color_graph();

	}

	void make_test_graph_big_branch(glm::vec3 dir, float z_offset, float stretch)
	{

		space_graph.clear();

		int node = 0;

		Constraint c;
		float dist = 50.f;
		dist = stretch;

		// start, 0
		SpaceNode sn;
		sn.name = "start";
		sn.position = glm::vec3(0, 0, 0);
		sn.color = glm::vec3(1.f, 0.58f, 0.04f);
		sn.is_solid = true;


		space_graph.push_back(sn);

		node++;

		// 1
		sn.name = "first mid";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 0;
		c.t_info = constraint_map[EdgeLabel::dive_spring];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);


		//node++;


		//2
		sn.name = "branch mid";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 0;
		c.t_info = constraint_map[EdgeLabel::long_jump];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);


		node++;

		// 3
		sn.name = "mid";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 1;
		c.t_info = constraint_map[EdgeLabel::jump];
		sn.constraints.push_back(c);


		c.index = 2;
		c.t_info = constraint_map[EdgeLabel::dive_spring];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);


		node++;

		// end, 4

		sn.name = "end";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 3;
		c.t_info = constraint_map[EdgeLabel::long_jump];
		sn.constraints.push_back(c);

		c.index = 9;
		c.t_info = constraint_map[EdgeLabel::jump];
		sn.constraints.push_back(c);

		c.index = 12;
		c.t_info = constraint_map[EdgeLabel::long_jump];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);


		node++;

		// 5

		sn.name = "other";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 2;
		c.t_info = constraint_map[EdgeLabel::jump];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);

		node++;

		// 6

		sn.name = "other";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 0;
		c.t_info = constraint_map[EdgeLabel::dive_spring];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);

		node++;

		// 7

		sn.name = "other";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 6;
		c.t_info = constraint_map[EdgeLabel::jump];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);

		node++;

		// 8

		sn.name = "other";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 7;
		c.t_info = constraint_map[EdgeLabel::jump];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);

		node++;

		// 9

		sn.name = "other";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 8;
		c.t_info = constraint_map[EdgeLabel::jump];
		sn.constraints.push_back(c);

		c.index = 5;
		c.t_info = constraint_map[EdgeLabel::dive_spring];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);

		node++;

		// 10

		sn.name = "other";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 3;
		c.t_info = constraint_map[EdgeLabel::long_jump];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);

		node++;

		// 11

		sn.name = "other";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 10;
		c.t_info = constraint_map[EdgeLabel::jump];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);

		node++;

		// 12

		sn.name = "other";
		sn.position = dir;
		sn.position *= node * dist;
		sn.position.z = -1.f * z_offset;
		sn.position = random_pos();
		sn.is_solid = true;
		sn.constraints.clear();

		c.index = 10;
		c.t_info = constraint_map[EdgeLabel::long_jump];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);

		node++;




		color_graph();

	}

	void color_graph()
	{


		for (int i = 0; i < space_graph.size(); i++)
		{
			if (space_graph[i].constraints.size() > 0)
			{
				for (Constraint& c : space_graph[i].constraints)
				{

					//check if within trajectory
					if (trajectory_test(c.t_info, space_graph[c.index].position, space_graph[i].position))
					{
						c.color = yes_col;
					}
					else
					{
						c.color = no_col;
					}

				}
			}

		}
		



	}

	glm::vec3 overshoot(glm::vec3 a, glm::vec3 b, float amnt)
	{

		glm::vec3 dir = b - a;
		glm::vec3 over_dir = glm::normalize(dir);
		over_dir *= amnt;
		return over_dir;


	}

	bool constraints_resolved()
	{
		for (int i = 0; i < space_graph.size(); i++)
		{
			if (space_graph[i].constraints.size() > 0)
			{
				for (const Constraint& c : space_graph[i].constraints)
				{

					//check if already within trajectory
					if (!trajectory_test(c.t_info, space_graph[c.index].position, space_graph[i].position))
					{

						return false;

					}
					else
					{
						//c.is_satisfied = true;
					}



				}
			}
		}
		return true;
	}

	void resolve_constraints()
	{

		for (int i = 0; i < space_graph.size(); i++)
		{
			if (space_graph[i].constraints.size() > 0)
			{
				for (const Constraint& c : space_graph[i].constraints)
				{

					//check if already within trajectory
					if (!trajectory_test(c.t_info, space_graph[c.index].position, space_graph[i].position))
					{
						//if not, find closest point and move there
						glm::vec3 closest = get_closest_point(c.t_info, space_graph[c.index].position, space_graph[i].position);
						space_graph[i].position = closest + overshoot(space_graph[i].position, closest, 0.1f);

						color_graph();						
						return;

					}
					else
					{
						//c.is_satisfied = true;
					}



				}
			}

		}
		color_graph();

	}

	void resolve_all_constraints()
	{
		int counter = 0;
		
		while (!constraints_resolved())
		{

			for (int i = 0; i < space_graph.size(); i++)
			{
				if (space_graph[i].constraints.size() > 0)
				{
					for (const Constraint& c : space_graph[i].constraints)
					{

						//check if already within trajectory
						if (!trajectory_test(c.t_info, space_graph[c.index].position, space_graph[i].position))
						{
							//if not, find closest point and move there
							glm::vec3 closest = get_closest_point(c.t_info, space_graph[c.index].position, space_graph[i].position);
							space_graph[i].position = closest + overshoot(space_graph[i].position, closest, 0.1f);

							color_graph();
							counter++;
							if (counter >= 100)
							{
								return;
							}
						}



					}
				}

			}
		}
		color_graph();


	}

	void construct_graph(Graph& graph)
	{
		// step through the graph and add each gameplay node to space graph


		space_graph.clear();

		// add each node to space graph

		auto nodes = graph.get_nodes();

		SpaceNode sn;
		for (auto node : nodes)
		{

			sn.name = node.second.get_name();
			if (sn.name == "start")
			{
				sn.position = glm::vec3(0, 0, 0);
			}
			else
			{
				sn.position = random_pos();
			}
			sn.is_hyper = false;

			space_graph.push_back(sn);
		}

		auto hyperedges = graph.get_hyperedges();

		for (auto hyperedge : hyperedges)
		{
			sn.name = hyperedge.second.get_name();
			sn.position = random_pos();
			sn.is_hyper = true;
			space_graph.push_back(sn);
		}

		// add each edge connection to space graph node constraints

		auto edges = graph.get_edges();

		for (auto edge : edges)
		{
			int source = -1;
			int target = -1;

			//find source and target nodes
			for (int i = 0; i < space_graph.size(); i++)
			{
				if (space_graph[i].name == edge.second.get_source())
				{
					source = i;
				}
				if (space_graph[i].name == edge.second.get_target())
				{
					target = i;
				}
			}
			if (source == -1 || target == -1)
			{
				continue;
			}

			//add constraint to target node
			Constraint c;
			c.t_info = constraint_map[edge.second.get_label()];
			c.index = source;

			space_graph[target].constraints.push_back(c);

		}

		//add each hyper edge connection to space graph node constraints

		for (auto hyperedge : hyperedges)
		{

			std::vector<int> targets;
			int source = -1;

			//find source and target nodes
			for (int i = 0; i < space_graph.size(); i++)
			{
				//find hyperedge
				if (space_graph[i].name == hyperedge.second.get_name())
				{
					source = i;
				}
				//find each connected node
				for (auto node : hyperedge.second.get_attachment_nodes())
				{
					if (space_graph[i].name == node)
					{
						targets.push_back(i);
					}
				}
			}
			if (source == -1 || targets.size() == 0)
			{
				continue;
			}

			//add constraint to target nodes
			Constraint c;

			for (int t : targets)
			{
				c.t_info = constraint_map[EdgeLabel::jump];
				c.index = source;
				c.is_hyper = true;

				space_graph[t].constraints.push_back(c);
			}
		}


	}

	void build_constraint_map()
	{

		EdgeLabel el = EdgeLabel::jump;
		TrajectoryInfo t;

		constraint_map[el] = t;

		t.velocity = 10.f;
		t.angle = (7.f * 3.14f) / 16.f;
		el = EdgeLabel::dive_spring;
		constraint_map[el] = t;

		el = EdgeLabel::backflip;
		constraint_map[el] = t;

		t.velocity = 15.f;
		t.angle = 3.14f / 8.f;
		el = EdgeLabel::long_jump;
		constraint_map[el] = t;

		el = EdgeLabel::kick;
		constraint_map[el] = t;

		el = EdgeLabel::deflect;
		constraint_map[el] = t;


		t.velocity = 10.f;
		t.angle = -1.3f;
		el = EdgeLabel::dive;
		constraint_map[el] = t;


		

	}

	glm::vec3 random_pos()
	{

		float x = ((rand() % 1000) * 0.05f) - 25.f;
		float y = ((rand() % 1000) * 0.05f) - 25.f;
		float z = ((rand() % 1000) * 0.05f) - 25.f;


		return glm::vec3(x, y, z);

	}

	float speed = 1.5f;


	float repulsion_dist = 5.0f;
	float attraction_dist = 6.0f;

	void particle_update(float speed, float dt)
	{
		// for each particle
		for (int i = 0; i < space_graph.size(); i++)
		{
			space_graph[i].velocity = glm::vec3(0, 0, 0);
			//check distance from each other particle
			for (int j = 0; j < space_graph.size(); j++)
			{
				if (i == j) { continue; }

				float dist = glm::distance(space_graph[i].position, space_graph[j].position);

				//check if particle is within repulsion distance
				if (dist < repulsion_dist)
				{
					//apply velocity away from other particle
					space_graph[i].velocity += glm::normalize(space_graph[i].position - space_graph[j].position);

				}

				bool connected = false;

				//check if particle is connected 
				for (Constraint c : space_graph[i].constraints)
				{
					if (c.index == j)
					{
						connected = true;
					}

				}
				for (Constraint c : space_graph[j].constraints)
				{

					if (c.index == i)
					{
						//connected = true;
					}


				}

				if (connected && (dist > attraction_dist))
				{
					//apply velocity towards other particle
					space_graph[i].velocity += glm::normalize(space_graph[j].position - space_graph[i].position);
				}


			}


			//space_graph[i].position += speed * glm::normalize(space_graph[i].velocity) * dt;
			space_graph[i].position += speed * space_graph[i].velocity * dt;
		}
		

	}


	void update(float dt)
	{




		for (int i = 0; i < space_graph.size(); i++)
		{
			if (space_graph[i].constraints.size() > 0)
			{
				for (const Constraint& c : space_graph[i].constraints)
				{

					//check if already within trajectory
					if (!trajectory_test(c.t_info, space_graph[c.index].position, space_graph[i].position))
					{
						//if not, find closest point and move towards it
						glm::vec3 closest = get_closest_point(c.t_info, space_graph[c.index].position, space_graph[i].position);
						//space_graph[i].position = closest + overshoot(space_graph[i].position, closest, 0.1f);

						glm::vec3 dir = closest - space_graph[i].position;
						//dir = glm::normalize(dir);
						space_graph[i].position += /*glm::normalize(dir) * (i + 1.f) * dt +*/ dir * speed * dt;

						color_graph();
						//return;

					}
					else
					{
						//c.is_satisfied = true;
					}



				}
			}

		}
		color_graph();

	}


	std::vector<SpaceNode> space_graph;
private:

	std::map<EdgeLabel, TrajectoryInfo> constraint_map;

	glm::vec3 yes_col = glm::vec3(0.f, 0.7f, 0.3f);
	glm::vec3 no_col = glm::vec3(0.86f, 0.1f, 0.13f);


};