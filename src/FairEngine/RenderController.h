#ifndef _RENDERCONTROLLER_H_
#define _RENDERCONTROLLER_H_
#include <memory>
#include <GL/glew.h>
#include <vector>

class Shader;
class Material;
class Texture;
class CubeMap;
class Light;
class ResourceManager;

/// \brief Handler for all render passes and post processing
class RenderController
{
	friend class Scene;
public:
	~RenderController();
	RenderController(){m_lightnum = 0;}

	void RegisterLight(std::weak_ptr<Light> _light);
	
private:
	void Generate();
	
	void ShadowPass();
	void GeomPass();
	void PostProcessPass();
	void Render();

	void ResizeBuffer();

	std::weak_ptr<ResourceManager> m_resourceManager;
	std::shared_ptr<Shader> m_postProcessShader;
	std::weak_ptr<Material> m_skyboxMat;
	std::weak_ptr<Material> m_shadowMat;
	std::weak_ptr<Texture> m_shadowTex;
	std::weak_ptr<CubeMap> m_skybox;
	std::weak_ptr<Light> m_lights[5];
	unsigned int m_lightnum;

	unsigned int m_shadowRes;

	GLuint m_shadowBufferIndex;
	GLuint m_shadowTextureIndex;

	GLuint m_QuadIndex;
	GLuint m_boxIndex;

	GLuint m_geomFrameBufferIndex;
	GLuint m_geomTextureBufferIndex;
	GLuint m_geomRenderBufferIndex;

	GLuint m_finalFrameBufferIndex;
	GLuint m_finalTextureBufferIndex;
};

#endif