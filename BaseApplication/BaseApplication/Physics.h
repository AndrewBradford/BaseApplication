#pragma once


#include <glm/glm.hpp>


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


	static float get_angle_between_vectors2(glm::vec2 a, glm::vec2 b)
	{
		float c = -1;
		if (b.y < 0) { c = 1; }
		return c * acosf(glm::dot(a, b) / (glm::length(a) * glm::length(b)));

	}





};