#pragma once

#include <GL/glew.h>
#include <vector>
#include <iostream>

class Shader;

class FrameBuffer
{
public:
	FrameBuffer(int screenWidth, int screenHeight);
	~FrameBuffer();
	void load();
	void firstPass();
	void secondPass();
	void render();
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int FBO;
	unsigned int TCB; // texture colour buffer
	unsigned int RBO; // render buffer object
	int screenWidth;
	int screenHeight;
	Shader* shader;
	void loadQuad();
	void loadFrameBuffer();
	void loadTextureColourBuffer();
	void loadRenderBuffer();
};

