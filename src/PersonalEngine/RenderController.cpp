#include "RenderController.h"
#include "Window.h"
#include "Shader.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Camera.h"
#include <string>

RenderController::~RenderController()
{
	glDeleteVertexArrays(1, &m_screenQuadIndex);
	glDeleteRenderbuffers(1, &m_sceneRenderBufferIndex);
	glDeleteTextures(1, &m_sceneTextureBufferIndex);
	glDeleteFramebuffers(1, &m_sceneFrameBufferIndex);
}

void RenderController::Generate()
{
	glGenFramebuffers(1, &m_sceneFrameBufferIndex);
	glBindFramebuffer(GL_FRAMEBUFFER, m_sceneFrameBufferIndex);

	glGenTextures(1, &m_sceneTextureBufferIndex);
	glBindTexture(GL_TEXTURE_2D, m_sceneTextureBufferIndex);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Window::GetWidth(),Window::GetHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D,0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_sceneTextureBufferIndex, 0);

	glGenRenderbuffers(1, &m_sceneRenderBufferIndex);
	glBindRenderbuffer(GL_RENDERBUFFER,m_sceneRenderBufferIndex);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,Window::GetWidth(),Window::GetHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_sceneRenderBufferIndex);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	float quadVertexPositions[] = {  
    -1.0f,  1.0f,
    -1.0f, -1.0f,
     1.0f, -1.0f,

    -1.0f,  1.0f,
     1.0f, -1.0f,
     1.0f,  1.0f
	};

	float quadVertexTexcoords[] = {
		0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f
	};

	glGenVertexArrays(1, &m_screenQuadIndex);
	glBindVertexArray(m_screenQuadIndex);

	GLuint positions;
	glGenBuffers(1, &positions);
	glBindBuffer(GL_ARRAY_BUFFER, positions);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12, &quadVertexPositions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	GLuint texcoords;
	glGenBuffers(1, &texcoords);
	glBindBuffer(GL_ARRAY_BUFFER, texcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12, &quadVertexTexcoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_postProcessShader = std::make_shared<Shader>("PPS","PostProcessVertex.txt","PostProcessFragment.txt");

}

void RenderController::ResizeBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_sceneFrameBufferIndex);

	glBindTexture(GL_TEXTURE_2D, m_sceneTextureBufferIndex);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Window::GetWidth(),Window::GetHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D,0);

	glBindRenderbuffer(GL_RENDERBUFFER,m_sceneRenderBufferIndex);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,Window::GetWidth(),Window::GetHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderController::Render()
{
	//calculate and set camera view and projection matricies in all materials before drawing to avoid repeated calls
	Camera::mainCamera.lock()->CalculateProjectionMatrix();
	Camera::mainCamera.lock()->CalculateViewMatrix();

	glBindFramebuffer(GL_FRAMEBUFFER, m_sceneFrameBufferIndex);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	Engine::m_currentScene->Render();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glUseProgram(m_postProcessShader->GetProgram());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_sceneTextureBufferIndex);

	glBindVertexArray(m_screenQuadIndex);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}