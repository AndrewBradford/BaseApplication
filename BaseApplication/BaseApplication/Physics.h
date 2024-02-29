#pragma once


#include <glm/glm.hpp>


class Physics
{

public:

	static bool trajectory_test(float velocity, float gravity, float angle, glm::vec3& point)
	{


		float point_x = point.x;
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








};