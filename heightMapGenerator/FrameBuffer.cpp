#include "FrameBuffer.h"
#include "Shader.h"

FrameBuffer::FrameBuffer(int screenWidth, int screenHeight)
{
	this->shader = new Shader("shaders/framebuffer.vert", "shaders/framebuffer.frag");
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

FrameBuffer::~FrameBuffer()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteFramebuffers(1, &this->FBO);
	glDeleteRenderbuffers(1, &this->RBO);
}

void FrameBuffer::load()
{
	this->loadQuad();
	this->loadFrameBuffer();
	this->loadTextureColourBuffer();
	this->loadRenderBuffer();
}

void FrameBuffer::firstPass()
{
	// bind to framebuffer and draw scene as we normally would to color texture 
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
	
	// make sure we clear the framebuffer's content
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
}

void FrameBuffer::secondPass()
{
	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	// clear all relevant buffers
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
}

void FrameBuffer::render()
{
	this->shader->use();
	glBindVertexArray(this->VAO);
	glBindTexture(GL_TEXTURE_2D, this->TCB);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


void FrameBuffer::loadQuad()
{
	float quadVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	
	this->shader->setInt("screenTexture", 0);
}

void FrameBuffer::loadFrameBuffer()
{
	glGenFramebuffers(1, &this->FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
}

void FrameBuffer::loadTextureColourBuffer()
{
	glGenTextures(1, &this->TCB);
	glBindTexture(GL_TEXTURE_2D, this->TCB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->screenWidth, this->screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->TCB, 0);
}

void FrameBuffer::loadRenderBuffer()
{
	glGenRenderbuffers(1, &this->RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->screenWidth, this->screenHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->RBO); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
