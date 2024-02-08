#include "Renderer.h"



#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"




//
//	FILE CURRENTLY UNUSED
//	FUNCTIONALITY MOVED TO GEOMETRY CLASS
// 
//	will remain until I figure out what to do with the texture loading functionality
// 



namespace Hollow {



	Renderer::Renderer()
	{

	}

	Renderer::~Renderer()
	{

	}

	void Renderer::init()
	{



	}

	unsigned int Renderer::loadTexture(const char* path)
	{
		//todo?
		// - store paths and ids of textures that have been loaded
		//		return id of already loaded


		int offset = texNum * (GL_TEXTURE1 - GL_TEXTURE0);
		
		if (texNum >= 16)
		{
			std::cout << "using 16 texture units!" << std::endl;
		}

		//bind texture object
		unsigned int texture;
		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0 + offset);
		glBindTexture(GL_TEXTURE_2D, texture);


		//configure texture object
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



		//load and generate texture
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load("res/container.jpg", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texure" << std::endl;
		}

		stbi_image_free(data);

		texNum++;

		return texture;
	}

	void Renderer::CreateVertexArray(float* vertices, size_t size, int posSize, int normSize, int colSize, int texSize)
	{

		/*
		unsigned int VBO;
		glGenBuffers(1, &VBO);

		CreateVertexArray(VBO, posSize, normSize, colSize, texSize);
		return;
*/

		//generate buffers
		unsigned int VBO, VAO, EBO;
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
		//glGenBuffers(1, &EBO);

		// bind vertex array object
		glBindVertexArray(VAO);

		// bind and set vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

		//bind and set element buffer
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		// Configure vertex Attributes
		
		int totSize = posSize + normSize + colSize + texSize;
		int bytePos = 0;
		int attribPos = 0;

		//position attribute
		if (posSize)
		{
			glVertexAttribPointer(0, posSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += posSize;
			attribPos++;
		}

		//normal attribute
		if (normSize)
		{
			glVertexAttribPointer(0, normSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += normSize;
			attribPos++;
		}

		//color attribute
		if (colSize)
		{
			glVertexAttribPointer(0, colSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += colSize;
			attribPos++;
		}

		//tex coord attribute
		if (texSize)
		{
			glVertexAttribPointer(0, texSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += texSize;
			attribPos++;
		}

		//unbind VBO (registered in attribs)
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		//cant unbind EBO while VAO is bound or will unbind EBO for the Vertex Array
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	}

	void Renderer::CreateVertexArray(float* vertices, size_t vSize, float* indices, size_t iSize,
		int posSize, int normSize, int colSize, int texSize)
	{

		//generate buffers
		unsigned int VBO, VAO, EBO;
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &EBO);

		// bind vertex array object
		glBindVertexArray(VAO);

		// bind and set vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vSize, vertices, GL_STATIC_DRAW);

		//bind and set element buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, indices, GL_STATIC_DRAW);


		// Configure vertex Attributes


		int totSize = posSize + normSize + colSize + texSize;
		int bytePos = 0;
		int attribPos = 0;

		//position attribute
		if (posSize)
		{
			glVertexAttribPointer(0, posSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += posSize;
			attribPos++;
		}

		//normal attribute
		if (normSize)
		{
			glVertexAttribPointer(0, normSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += normSize;
			attribPos++;
		}

		//color attribute
		if (colSize)
		{
			glVertexAttribPointer(0, colSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += colSize;
			attribPos++;
		}

		//tex coord attribute
		if (texSize)
		{
			glVertexAttribPointer(0, texSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += texSize;
			attribPos++;
		}

		//unbind VBO (registered in attribs)
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		//cant unbind EBO while VAO is bound or will unbind EBO for the Vertex Array
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	}

	void Renderer::CreateVertexArray(unsigned int vboID, int posSize, int normSize, int colSize, int texSize)
	{

		//generate buffers
		unsigned int VBO, VAO, EBO;
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
		//glGenBuffers(1, &EBO);

		// bind vertex array object
		glBindVertexArray(VAO);

		// bind and set vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vboID);

		//bind and set element buffer
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		// Configure vertex Attributes

		int totSize = posSize + normSize + colSize + texSize;
		int bytePos = 0;
		int attribPos = 0;

		//position attribute
		if (posSize)
		{
			glVertexAttribPointer(0, posSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += posSize;
			attribPos++;
		}

		//normal attribute
		if (normSize)
		{
			glVertexAttribPointer(0, normSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += normSize;
			attribPos++;
		}

		//color attribute
		if (colSize)
		{
			glVertexAttribPointer(0, colSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += colSize;
			attribPos++;
		}

		//tex coord attribute
		if (texSize)
		{
			glVertexAttribPointer(0, texSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += texSize;
			attribPos++;
		}

		//unbind VBO (registered in attribs)
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		//cant unbind EBO while VAO is bound or will unbind EBO for the Vertex Array
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	}

	void Renderer::CreateVertexArray(unsigned int vboID, float* indices, size_t iSize, int posSize, int normSize, int colSize, int texSize)
	{

		//generate buffers
		unsigned int VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &EBO);

		// bind vertex array object
		glBindVertexArray(VAO);

		// bind premade vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vboID);

		//bind and set element buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, indices, GL_STATIC_DRAW);


		// Configure vertex Attributes


		int totSize = posSize + normSize + colSize + texSize;
		int bytePos = 0;
		int attribPos = 0;

		//position attribute
		if (posSize)
		{
			glVertexAttribPointer(0, posSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += posSize;
			attribPos++;
		}

		//normal attribute
		if (normSize)
		{
			glVertexAttribPointer(0, normSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += normSize;
			attribPos++;
		}

		//color attribute
		if (colSize)
		{
			glVertexAttribPointer(0, colSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += colSize;
			attribPos++;
		}

		//tex coord attribute
		if (texSize)
		{
			glVertexAttribPointer(0, texSize, GL_FLOAT, GL_FALSE, totSize * sizeof(float), (void*)bytePos);
			glEnableVertexAttribArray(attribPos);
			bytePos += texSize;
			attribPos++;
		}

		//unbind VBO (registered in attribs)
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		//cant unbind EBO while VAO is bound or will unbind EBO for the Vertex Array
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	}


}