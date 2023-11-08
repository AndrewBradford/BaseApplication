#pragma once



#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Shapes.h"

namespace Hollow {

	


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

	struct EBuffer
	{
		bool used = false;
		unsigned int ID;
		unsigned int indexNum;
	};

	struct VertexUsage 
	{
		bool useNormal;
		bool useColor;
		bool useTexCoord;
	};

	struct VArray
	{
		unsigned int ID;

		VBuffer VBO;
		EBuffer EBO;

		bool useNormal;
		bool useColor;
		bool useTexCoord;


	};


	class Geometry
	{


	public:

		static VArray SetupVAO(Hollow::Shape* shape);
		static VArray SetupVAO(Hollow::Shape* shape, VBuffer VBO);
		static void DrawVArray(VArray VAO);

	private:


	};

}
