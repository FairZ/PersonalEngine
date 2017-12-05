#ifndef _RENDERCONTROLLER_H_
#define _RENDERCONTROLLER_H_
#include <memory>
#include <GL/glew.h>
#include <vector>

class Shader;
class Light;
class ResourceManager;

class RenderController
{
	friend class Scene;
public:
	~RenderController();
	RenderController(){m_lightnum = 0;}

	void RegisterLight(std::weak_ptr<Light> _light);
	
private:
	void Generate();
	
	void Render();

	void ResizeBuffer();

	std::weak_ptr<ResourceManager> m_resourceManager;
	std::shared_ptr<Shader> m_postProcessShader;
	std::weak_ptr<Light> m_lights[5];
	unsigned int m_lightnum;

	GLuint m_screenQuadIndex;
	GLuint m_sceneFrameBufferIndex;
	GLuint m_sceneTextureBufferIndex;
	GLuint m_sceneRenderBufferIndex;
};

#endif