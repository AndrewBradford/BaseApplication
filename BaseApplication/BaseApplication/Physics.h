#pragma once


#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "HyperEdgeGrammar.h"



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

};

struct SpaceNode {

	std::string name;
	glm::vec3 position;
	std::vector<Constraint> constraints;

	bool is_solid = true;

	glm::vec3 color;
};

class Physics
{

public:

	static bool trajectory_test(float velocity, float gravity, float angle, glm::vec3& origin, glm::vec3& point)
	{

		glm::vec3 proj = point - origin;
		proj.y = 0.f;



		float point_x = glm::length(proj);
		float point_y = point.y;

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

	static bool trajectory_test(TrajectoryInfo t, glm::vec3& origin, glm::vec3& point)
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


	static glm::vec3 get_closest_point(float velocity, float gravity, float angle, glm::vec3& origin, glm::vec3& point)
	{


		glm::vec3 proj = point - origin;
		proj.y = 0.f;


		float point_x = glm::length(proj);
		float point_y = point.y;


		float a = point_x;
		float b = point_y;

		float c = tanf(angle);

		float d = gravity / (2 * velocity * velocity * cosf(angle) * cosf(angle));

		float closest_val = 10000.f;
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

		return closest_point;



	}


	Physics()
	{
		build_constraint_map();
		make_test_graph(glm::vec3(1, 0, 0));
	}

	~Physics()
	{

	}

	//void add_Node(Constraint c, int )

	void make_test_graph(glm::vec3 dir)
	{

		SpaceNode sn;
		sn.name = "start";
		sn.position = glm::vec3(0, 0, 0);
		sn.color = glm::vec3(1, 1, 1);
		sn.is_solid = true;
		
		
		space_graph.push_back(sn);


		sn.name = "end";
		sn.position = dir;
		sn.position *= 20.f;
		sn.is_solid = true;
		sn.constraints.clear();
				
		Constraint c;
		c.index = 0;
		c.t_info = constraint_map[EdgeLabel::dive_spring];
		sn.constraints.push_back(c);

		space_graph.push_back(sn);


	}

	void construct_graph(Graph* graph, glm::vec3 dir)
	{
		// step through the graph and add each gameplay node to space graph

		Node* current_node = graph->get_external_node(0);

		SpaceNode sn;
		sn.name = current_node->get_name();
		sn.position = glm::vec3(0, 0, 0);

		



	}

	void build_constraint_map()
	{

		EdgeLabel el = EdgeLabel::jump;
		TrajectoryInfo t;

		constraint_map[el] = t;

		t.velocity = 15.f;
		t.angle = (7.f * 3.14f) / 16.f;
		el = EdgeLabel::dive_spring;
		constraint_map[el] = t;

		t.velocity = 20.f;
		t.angle = 3.14f / 8.f;
		el = EdgeLabel::long_jump;
		constraint_map[el] = t;

		

	}

	

	std::vector<SpaceNode> space_graph;
private:

	std::map<EdgeLabel, TrajectoryInfo> constraint_map;


};