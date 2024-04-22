#pragma once



#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Shapes.h"

namespace Hollow {

	

	// Vertex Buffer Object wrapper
	struct VBuffer
	{
		unsigned int ID;

		unsigned int stride;
		unsigned int vertNum;

		unsigned int PositionBytes;
		unsigned int NormalBytes;
		unsigned int ColorBytes;
		unsigned int TexCoordBytes;


	};

	// Element Buffer Object wrapper
	struct EBuffer
	{
		bool used = false;
		unsigned int ID;
		unsigned int indexNum;
	};

	// definition of what elements vertex uses
	struct VertexUsage 
	{
		bool useNormal;
		bool useColor;
		bool useTexCoord;
	};

	// Vertex Array Object wrapper
	struct VArray
	{
		unsigned int ID;

		VBuffer VBO;
		EBuffer EBO;

		// which vertex attributes are used
		bool useNormal;
		bool useColor;
		bool useTexCoord;


	};


	class Geometry
	{


	public:

		//set up vertex array object based on shape vertices
		static VArray SetupVAO(Hollow::Shape* shape);

		//set up vertex array object based on shape, using existing vertex buffer object
		static VArray SetupVAO(Hollow::Shape* shape, VBuffer VBO);

		// draw a vertex array as triangles
		static void DrawVArray(VArray VAO);

		//draw a vertex array as lines
		static void DrawVArrayLine(VArray VAO);

		//draw a vertex array as a line strip
		static void DrawVArrayLineStrip(VArray VAO);

	private:


	};

}
