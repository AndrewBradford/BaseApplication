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

private:

	std::map<EdgeLabel, TrajectoryInfo> constraint_map;

	glm::vec3 yes_col = glm::vec3(0.f, 0.7f, 0.3f);
	glm::vec3 no_col = glm::vec3(0.86f, 0.1f, 0.13f);


	float speed = 1.5f;


	float repulsion_dist = 5.0f;
	float attraction_dist = 6.0f;





public:

	Physics();

	~Physics();

	std::vector<SpaceNode> space_graph;

	// make space graph from grammar graph
	void construct_graph(Graph& graph);

	// setup trajectory info for each move
	void build_constraint_map();

	// make a simple example level
	void make_test_graph(glm::vec3 dir, float z_offset, float stretch);

	// make a simple branching example level
	void make_test_graph_branch(glm::vec3 dir, float z_offset, float stretch);

	// make a more complex branching example level
	void make_test_graph_big_branch(glm::vec3 dir, float z_offset, float stretch);

	// set the color of each constraint
	void color_graph();

	// true if point lies under trajectory
	static bool trajectory_test(float velocity, float gravity, float angle, glm::vec3 origin, glm::vec3 point);

	// true if point lies under trajectory
	static bool trajectory_test(TrajectoryInfo t, glm::vec3 origin, glm::vec3 point);

	static float get_angle_between_vectors2(glm::vec2 a, glm::vec2 b);

	// get y value at trajectory x point
	static float get_y_at_x(float velocity, float gravity, float angle, float x);

	// get y value at trajectory x point
	static float get_y_at_x(TrajectoryInfo t, float x);

	// find point on trajectory with shortest distance to target point
	static glm::vec3 get_closest_point(float velocity, float gravity, float angle, glm::vec3 origin, glm::vec3 point);

	// find point on trajectory with shortest distance to target point
	glm::vec3 get_closest_point(TrajectoryInfo t, glm::vec3 origin, glm::vec3 point);

	// (Not Implemented) find closest point in two trajectories to point
	glm::vec3 get_closest_crossover_point(TrajectoryInfo t1, TrajectoryInfo t2, glm::vec3 origin, glm::vec3 point1, glm::vec3 point2);

	// move from a to be and overshoot b by amount (returns the overshoot vector to add to b)
	glm::vec3 overshoot(glm::vec3 a, glm::vec3 b, float amnt);

	// returns true of all constraints are satisfied
	bool constraints_resolved();

	// resolve a single constraint
	void resolve_constraints();

	// resolve all constraints
	void resolve_all_constraints();

	// update positions of platforms by particle-sim-like movement
	void particle_update(float speed, float dt);

	// (not implemented) alternate particle sim update
	void update(float dt);

	// gather data for a single space
	void get_data(float& line, float& grad, int& unin, int& sequ);


private:

	// generate a random point in a 50 unit cube (origin in centre)
	glm::vec3 random_pos();


};