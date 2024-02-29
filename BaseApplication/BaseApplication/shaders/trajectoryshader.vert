
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float gravity;
uniform float angle;
uniform float velocity;



void main()
{

	float x = aPos.x;
	float cosa = cos(angle);
	float y = x * (tan(angle) - (x * (gravity / (2 * velocity * velocity * cosa * cosa))));


	vec3 v = aPos;
	v.y = y;

   gl_Position = projection * view * model * vec4(v, 1.0);

}