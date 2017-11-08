#ifndef _RESOUIRCEMANAGER_H_
#define _RESOUIRCEMANAGER_H_

#include <vector>
#include <string>
#include <memory>

class Material;
class Shader;
class Texture;
class Mesh;

class ResourceManager
{
	friend class Scene;
public:
	std::weak_ptr<Shader> GetShader(std::string _shaderName);
	std::weak_ptr<Material> GetMaterial(std::string _materialName);
	std::weak_ptr<Texture> GetTexture(std::string _textureName);
	std::weak_ptr<Mesh> GetMesh(std::string _meshName);

private:
	std::vector<std::shared_ptr<Shader>> m_shaders;
	std::vector<std::shared_ptr<Material>> m_materials;
	std::vector<std::shared_ptr<Texture>> m_textures;
	std::vector<std::shared_ptr<Mesh>> m_meshes;

	//void LoadResources(std::string _fileName){} add soon
	
	void AddShader(std::string _vertTXT, std::string _fragTXT, std::string _shaderName);
	void AddMaterial(std::weak_ptr<Shader> _baseShader, std::string _materialName);
	void AddTexture(std::string _filePath, std::string _textureName);
	void AddMesh(std::string _filePath, std::string _meshName);
};


#endif