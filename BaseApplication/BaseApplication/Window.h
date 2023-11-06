#pragma once



#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>


class Window
{


public:

	Window();
	~Window();

	//start the window
	bool createWindowGL(const char* name, int w, int h);
	
	//register GLFW callbacks
	void registerFramebufferSizeCallback(GLFWframebuffersizefun callback);
	void registerCursorPosCallback(GLFWcursorposfun callback);

	//should the window close
	bool ShouldClose();
	void CloseWindow();

	//terminate glfw
	void terminate();

	//retrieve frame time
	float getDeltaTime();

	void endFrame();

	//resize framebuffer callback
	//void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:

	GLFWwindow* window = nullptr;

	float currentFrame = 0.0f;
	float lastFrame = 0.0f;

};

