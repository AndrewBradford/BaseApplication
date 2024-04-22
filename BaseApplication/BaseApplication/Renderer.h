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



//
//	FILE CURRENTLY UNUSED
//	FUNCTIONALITY MOVED TO GEOMETRY CLASS
// 

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



}