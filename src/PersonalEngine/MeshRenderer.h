#ifndef _MESHRENDERER_H_
#define _MESHRENDERER_H_
#include "Component.h"
#include <memory>
#include <string>

class Mesh;
class Material;

/// \brief Component for rendering meshes
class MeshRenderer : public Component
{
public:
	void SetMesh(std::string _meshName);
	void SetMaterial(std::string _materialName);
	std::weak_ptr<Material> GetMaterial();
private:
	std::weak_ptr<Mesh> m_mesh;
	std::weak_ptr<Material> m_material;
	
	std::string modelMat;

	void Awake();
	void Render();
};

#endif