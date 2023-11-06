#pragma once

#include "Window.h"


#include <iostream>


class Renderer
{

public:

	Renderer();
	~Renderer();

	Window* init();



private:

	///GLFWwindow* window = nullptr;
	Window* window = nullptr;



};

