#include "Shader.h"



namespace Hollow {


	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		//mostly copied from learnopengl
		//retrieve shader code

		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			//open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			//read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//close file handlers
			vShaderFile.close();
			fShaderFile.close();
			//convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();


		//compile shaders

		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		//vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		//print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};


		//fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		//print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		};


		//shader program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		//print linking errors if any
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// delete shaders - linked now and dont care anymore!
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	};



	void LitShader::UseShader(glm::mat4& model, glm::mat4& view, glm::mat4& proj, glm::vec3& objectCol, glm::vec3& lightCol, glm::vec3& lightPos, glm::vec3& camPos)
	{

		glUseProgram(ID);

		//set uniforms
		//vertex shader
		setMatrix4f("model", model);
		setMatrix4f("view", view);
		setMatrix4f("projection", proj);

		//fragment shader
		setVec3("objectColor", objectCol);
		setVec3("lightColor", lightCol);
		setVec3("lightPos", lightPos);
		setVec3("viewPos", camPos);


	}

	void FlatShader::UseShader(glm::mat4& model, glm::mat4& view, glm::mat4& proj, glm::vec3 objectCol)
	{

		glUseProgram(ID);

		//set uniforms
		//vertex shader
		setMatrix4f("model", model);
		setMatrix4f("view", view);
		setMatrix4f("projection", proj);

		//fragment shader
		setVec3("objectColor", objectCol);

	}

	void TexShader::UseShader(glm::mat4& model, glm::mat4& view, glm::mat4& proj
		, unsigned int texID, unsigned int texUnit)
	{

		glUseProgram(ID);

		//set uniforms
		//vertex shader
		setMatrix4f("model", model);
		setMatrix4f("view", view);
		setMatrix4f("projection", proj);

		setInt("texture1", 0);


		glActiveTexture(texUnit);
		glBindTexture(GL_TEXTURE_2D, texID);


	}

}