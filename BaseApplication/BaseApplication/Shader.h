
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


namespace Hollow {


	

	class Shader
	{

	public:

		//read and compile shaders into shader program
		Shader(const char* vertexPath, const char* fragmentPath);
		

		// Functions for setting uniforms
		void setBool(const std::string& name, bool value) const
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
		}
		void setInt(const std::string& name, int value) const
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
		}
		void setFloat(const std::string& name, float value) const
		{
			glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
		}

		void setFloat3(const std::string& name, float v1, float v2, float v3) const
		{
			glUniform3f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3);
		}

		void setVec3(const std::string& name, glm::vec3& vector) const
		{
			glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vector[0]);
		}

		void setMatrix4f(const std::string& name, glm::mat4& matrix) const
		{
			glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
		}


	protected:
		//program id
		unsigned int ID;

	};


	class LitShader : public Shader
	{


	public:


		LitShader()
			: Shader{ "shaders/shader.vert", "shaders/shader.frag" }
		{
		};
		~LitShader() {};

		void UseShader(glm::mat4& model, glm::mat4& view, glm::mat4& proj,
			glm::vec3& objectCol, glm::vec3& lightCol, glm::vec3& lightPos, glm::vec3& camPos);

	};

	class FlatShader : public Shader
	{
	public:

		FlatShader()
			: Shader{ "shaders/lightshader.vert", "shaders/lightshader.frag" }
		{
		};
		~FlatShader() {};

		void UseShader(glm::mat4& model, glm::mat4& view, glm::mat4& proj, glm::vec3 objectCol);

	};

	class LineShader : public Shader
	{
	public:
		LineShader()
			: Shader{ "shaders/lineshader.vert","shaders/lineshader.frag" }
		{
		};
		~LineShader() {};

		void UseShader(glm::vec3& start, glm::vec3& end, glm::mat4& model, glm::mat4& view, glm::mat4& proj, glm::vec3 objectCol);
	};

	class TexShader : public Shader
	{
		TexShader(const char* vertexPath, const char* fragmentPath)
			: Shader{ vertexPath, fragmentPath }
		{
		};
		~TexShader() {};

		void UseShader(glm::mat4& model, glm::mat4& view, glm::mat4& proj, unsigned int texID, unsigned int texUnit);


	};


}

#endif