#pragma once


namespace Hollow {




	class Shape
	{
	public:

		Shape(int vnum, int s, int inum, int ps, int ns, int cs, int ts) :
			vertNum{ vnum }, stride{ s }, indNum{ inum }, PosSize{ ps }, NormSize{ ns }, ColSize{ cs }, TexSize{ ts } {}
		~Shape() {};


		int vertNum;
		int stride;
		
		int indNum;

		int PosSize;
		int NormSize;
		int ColSize;
		int TexSize;


		virtual size_t getVertexSize() = 0;
		virtual float* getVertexRef() = 0;

		virtual size_t getIndexSize() = 0;
		virtual float* getIndexRef() = 0;



	};

	class Cube : public Shape
	{

	public:

		Cube() : Shape{36,6,0,3,3,0,0}
		{
		};
		~Cube() {};

		float vertices[36 * 6] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};


		size_t getVertexSize() override {
			return sizeof(vertices);
		}
		float* getVertexRef() override {
			return vertices;
		}

		size_t getIndexSize() override {
			return 0;
		}
		float* getIndexRef() override {
			return nullptr;
		}

	};


	class Line : public Shape
	{

	public:

		Line() : Shape{ 2,3,0,3,0,0,0 }
		{
		};
		~Line() {};

		float vertices[2 * 3] = {
			0.f, 0.f, 0.f,
			1.f, 1.f, 1.f
		};


		size_t getVertexSize() override {
			return sizeof(vertices);
		}
		float* getVertexRef() override {
			return vertices;
		}

		size_t getIndexSize() override {
			return 0;
		}
		float* getIndexRef() override {
			return nullptr;
		}

	};

	class Trajectory : public Shape
	{

	public:

		Trajectory() : Shape{ 100,3,0,3,0,0,0 }
		{

			for (int i = 0; i < 100; i++)
			{
				vertices[i * 3 + 0] = i * 0.5f;
				vertices[i * 3 + 1] = 0.f;
				vertices[i * 3 + 2] = 0.f;

			}

		};
		~Trajectory() {};

		float vertices[100 * 3];


		size_t getVertexSize() override {
			return sizeof(vertices);
		}
		float* getVertexRef() override {
			return vertices;
		}

		size_t getIndexSize() override {
			return 0;
		}
		float* getIndexRef() override {
			return nullptr;
		}

	};


}
