#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iostream>




namespace Hollow {





	class Renderer
	{

	public:



		Renderer();
		~Renderer();

		void init();

		unsigned int loadTexture(const char* path);

		// set up vertex array object
		void CreateVertexArray(float * vertices, size_t size, 
			int posSize, int normSize, int colSize, int texSize);
		// set up vertex array object with element buffer
		void CreateVertexArray(float* vertices, size_t vSize, float* indices, size_t iSize,
			int posSize, int normSize, int colSize, int texSize);

		// set up vertex array object using a premade vertex buffer
		void CreateVertexArray(unsigned int vboID, int posSize, int normSize, int colSize, int texSize);
		// set up vertex array object with element buffer using a premade vertex buffer
		void CreateVertexArray(unsigned int vboID, float* indices, size_t iSize,
			int posSize, int normSize, int colSize, int texSize);



	private:


		int texNum = 0;

	};

	/*
	namespace Shader {



		static unsigned int loadShader(const char* vertexPath, const char* fragmentPath)
		{

			unsigned int id;

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
			id = glCreateProgram();
			glAttachShader(id, vertex);
			glAttachShader(id, fragment);
			glLinkProgram(id);
			//print linking errors if any
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(id, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			}

			// delete shaders - linked now and dont care anymore!
			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return id;

		}

		static void setBool(unsigned int ID, const std::string& name, bool value)
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
		}

		static void setInt(unsigned int ID, const std::string& name, int value)
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
		}
		
		static void setFloat(unsigned int ID, const std::string& name, float value)
		{
			glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
		}

		static void setMatrix4f(unsigned int ID, const std::string& name, glm::mat4& matrix)
		{
			glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
		}



	}*/



}