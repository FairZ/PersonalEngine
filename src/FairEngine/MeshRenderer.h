#ifndef _MESHRENDERER_H_
#define _MESHRENDERER_H_
#include "Component.h"
#include <memory>
#include <vector>
#include <string>

class Mesh;
class Material;

/// \brief Component for rendering meshes
class MeshRenderer : public Component
{
public:
	void SetMesh(std::string _meshName);
	void SetMaterial(unsigned int _index, std::string _materialName);
	std::weak_ptr<Material> GetMaterial(unsigned int _index);
private:
	std::weak_ptr<Mesh> m_model;
	std::vector<std::weak_ptr<Material>> m_materials;
	std::weak_ptr<Material> m_shadowMat;
	
	std::string modelMat;

	void Awake();
	void Render();
	void ShadowRender();
};

#endif