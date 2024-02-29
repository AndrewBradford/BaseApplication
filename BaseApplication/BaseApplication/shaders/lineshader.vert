
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 startPos;
uniform vec3 endPos;

void main()
{

	vec3 v = startPos;
	v.x = v.x + aPos.x * (endPos.x - startPos.x);
	v.y = v.y + aPos.y * (endPos.y - startPos.y);
	v.z = v.z + aPos.z * (endPos.z - startPos.z);

   gl_Position = projection * view * model * vec4(v, 1.0);

}
