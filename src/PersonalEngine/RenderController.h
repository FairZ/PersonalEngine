#ifndef _RENDERCONTROLLER_H_
#define _RENDERCONTROLLER_H_

#include <GL/glew.h>
#include <memory>

class Shader;

class RenderController
{
public:
	~RenderController();
	void Generate();
	
	void Render();

	void ResizeBuffer();
private:
	std::shared_ptr<Shader> m_postProcessShader;

	GLuint m_screenQuadIndex;
	GLuint m_sceneFrameBufferIndex;
	GLuint m_sceneTextureBufferIndex;
	GLuint m_sceneRenderBufferIndex;
};

#endif