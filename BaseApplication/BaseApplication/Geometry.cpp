#include "Geometry.h"

#include "Shapes.h"

#include <iostream>

namespace Hollow {




	VArray Geometry::SetupVAO(Hollow::Shape* shape)
	{


		VBuffer VBO;
		EBuffer EBO;
		VArray VAO;


		//assemble VBO container
		VBO.stride = shape->stride;
		VBO.vertNum = shape->vertNum;
		VBO.PositionBytes = shape->PosSize;
		VBO.NormalBytes = shape->NormSize;
		VBO.ColorBytes = shape->ColSize;
		VBO.TexCoordBytes = shape->TexSize;

		//assemble EBO container
		EBO.used = shape->indNum;
		EBO.indexNum = shape->indNum;

		//assemble VAO container
		VAO.useNormal = true;
		VAO.useColor = false;
		VAO.useTexCoord = false;



		//generate buffers
		glGenBuffers(1, &(VBO.ID));
		glGenVertexArrays(1, &(VAO.ID));
		//glGenBuffers(1, &(EBO.ID));

		VAO.VBO = VBO;
		VAO.EBO = EBO;

		//bind VAO
		glBindVertexArray(VAO.ID);


		//bind and set VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO.ID);
		glBufferData(GL_ARRAY_BUFFER, shape->getVertexSize(), shape->getVertexRef(), GL_STATIC_DRAW);

		if (shape->indNum)
		{
			//bind and set EBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO.ID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape->getIndexSize(), shape->getIndexRef(), GL_STATIC_DRAW);
		}

		//configure vertex attributes
		
		int bytePos = 0;
		int attribPos = 0;

		//position attribute
		if (true)
		{
			glVertexAttribPointer(attribPos, VBO.PositionBytes, GL_FLOAT, GL_FALSE, VAO.VBO.stride * sizeof(float), (void*)(bytePos * sizeof(float)));
			glEnableVertexAttribArray(attribPos);
			bytePos += VBO.PositionBytes;
			attribPos++;
		}

		//normal attribute
		if (shape->NormSize)
		{
			glVertexAttribPointer(attribPos, VBO.NormalBytes, GL_FLOAT, GL_FALSE, VAO.VBO.stride * sizeof(float), (void*)(bytePos * sizeof(float)));
			glEnableVertexAttribArray(attribPos);
			bytePos += VBO.NormalBytes;
			attribPos++;
		}

		//color attribute
		if (shape->ColSize)
		{
			glVertexAttribPointer(attribPos, VBO.ColorBytes, GL_FLOAT, GL_FALSE, VAO.VBO.stride * sizeof(float), (void*)(bytePos * sizeof(float)));
			glEnableVertexAttribArray(attribPos);
			bytePos += VBO.ColorBytes;
			attribPos++;
		}

		//tex coord attribute
		if (shape->TexSize)
		{
			glVertexAttribPointer(attribPos, VBO.TexCoordBytes, GL_FLOAT, GL_FALSE, VAO.VBO.stride * sizeof(float), (void*)(bytePos * sizeof(float)));
			glEnableVertexAttribArray(attribPos);
			bytePos += VBO.TexCoordBytes;
			attribPos++;
		}


		//unbind VBO (registered in attribs)
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		//cant unbind EBO while VAO is bound or will unbind EBO for the Vertex Array
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		return VAO;
	}



	VArray Geometry::SetupVAO(Hollow::Shape* shape, VBuffer VBO)
	{


		EBuffer EBO;
		VArray VAO;


		//assemble EBO container
		EBO.used = shape->indNum;
		EBO.indexNum = shape->indNum;

		//assemble VAO container
		VAO.useNormal = false;
		VAO.useColor = false;
		VAO.useTexCoord = false;



		//generate buffers
		glGenVertexArrays(1, &(VAO.ID));
		//glGenBuffers(1, &(EBO.ID));

		VAO.VBO = VBO;
		VAO.EBO = EBO;

		//bind VAO
		glBindVertexArray(VAO.ID);

		//bind and set VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO.ID);

		if (shape->indNum)
		{
			//bind and set EBO
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO.ID);
			//glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape->getIndexSize(), shape->getIndexRef(), GL_STATIC_DRAW);
		}

		//configure vertex attributes

		int bytePos = 0;
		int attribPos = 0;

		//position attribute
		if (shape->PosSize)
		{
			glVertexAttribPointer(attribPos, shape->PosSize, GL_FLOAT, GL_FALSE, shape->stride * sizeof(float), (void*)(bytePos * sizeof(float)));
			glEnableVertexAttribArray(attribPos);
			bytePos += shape->PosSize;
			attribPos++;
		}

		//normal attribute
		if (VAO.useNormal)
		{
			glVertexAttribPointer(attribPos, shape->NormSize, GL_FLOAT, GL_FALSE, shape->stride * sizeof(float), (void*)(bytePos * sizeof(float)));
			glEnableVertexAttribArray(attribPos);
			bytePos += shape->NormSize;
			attribPos++;
		}
		
		//color attribute
		if (VAO.useColor)
		{
			glVertexAttribPointer(attribPos, shape->ColSize, GL_FLOAT, GL_FALSE, shape->stride * sizeof(float), (void*)(bytePos * sizeof(float)));
			glEnableVertexAttribArray(attribPos);
			bytePos += shape->ColSize;
			attribPos++;
		}

		//tex coord attribute
		if (VAO.useTexCoord)
		{
			glVertexAttribPointer(attribPos, shape->TexSize, GL_FLOAT, GL_FALSE, shape->stride * sizeof(float), (void*)(bytePos * sizeof(float)));
			glEnableVertexAttribArray(attribPos);
			bytePos += shape->TexSize;
			attribPos++;
		}


		//unbind VBO (registered in attribs)
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		//cant unbind EBO while VAO is bound or will unbind EBO for the Vertex Array
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		return VAO;
	}

	void Geometry::DrawVArray(VArray VAO)
	{

		glBindVertexArray(VAO.ID);
		glDrawArrays(GL_TRIANGLES, 0, 36);


	}

	void Geometry::DrawVArrayLine(VArray VAO)
	{

		glBindVertexArray(VAO.ID);
		glDrawArrays(GL_LINES, 0, 2);


	}

}

