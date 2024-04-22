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

	static bool trajectory_test(float velocity, float gravity, float angle, glm::vec3 origin, glm::vec3 point);

	static bool trajectory_test(TrajectoryInfo t, glm::vec3 origin, glm::vec3 point);


	static float get_angle_between_vectors2(glm::vec2 a, glm::vec2 b);


	static float get_y_at_x(float velocity, float gravity, float angle, float x);

	static float get_y_at_x(TrajectoryInfo t, float x);


	static glm::vec3 get_closest_point(float velocity, float gravity, float angle, glm::vec3 origin, glm::vec3 point);

	glm::vec3 get_closest_point(TrajectoryInfo t, glm::vec3 origin, glm::vec3 point);

	glm::vec3 get_closest_crossover_point(TrajectoryInfo t1, TrajectoryInfo t2, glm::vec3 origin, glm::vec3 point1, glm::vec3 point2);

	Physics();

	~Physics();


	void make_test_graph(glm::vec3 dir, float z_offset, float stretch);

	void make_test_graph_branch(glm::vec3 dir, float z_offset, float stretch);

	void make_test_graph_big_branch(glm::vec3 dir, float z_offset, float stretch);

	void color_graph();

	glm::vec3 overshoot(glm::vec3 a, glm::vec3 b, float amnt);

	bool constraints_resolved();

	void resolve_constraints();

	void resolve_all_constraints();

	void construct_graph(Graph& graph);

	void build_constraint_map();

	glm::vec3 random_pos();

	float speed = 1.5f;


	float repulsion_dist = 5.0f;
	float attraction_dist = 6.0f;

	void particle_update(float speed, float dt);


	void update(float dt);

	void get_data(float& line, float& grad, int& unin, int& sequ);


	std::vector<SpaceNode> space_graph;
private:

	std::map<EdgeLabel, TrajectoryInfo> constraint_map;

	glm::vec3 yes_col = glm::vec3(0.f, 0.7f, 0.3f);
	glm::vec3 no_col = glm::vec3(0.86f, 0.1f, 0.13f);


};