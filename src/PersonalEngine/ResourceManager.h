#ifndef _RESOUIRCEMANAGER_H_
#define _RESOUIRCEMANAGER_H_

#include <vector>
#include <string>
#include <memory>

class Material;
class Shader;
class Texture;
class Mesh;
class CubeMap;

/// \brief Handler for loading and getting resources within a scene
class ResourceManager
{
	friend class Scene;
	friend class RenderController;

public:
	std::weak_ptr<Shader> GetShader(std::string _shaderName);
	std::weak_ptr<Material> GetMaterial(std::string _materialName);
	std::weak_ptr<Texture> GetTexture(std::string _textureName);
	std::weak_ptr<CubeMap> GetCubeMap(std::string _cubeMapName);
	std::weak_ptr<Mesh> GetMesh(std::string _meshName);

	ResourceManager();

private:
	std::vector<std::shared_ptr<Shader>> m_shaders;
	std::vector<std::shared_ptr<Material>> m_materials;
	std::vector<std::shared_ptr<Texture>> m_textures;
	std::vector<std::shared_ptr<CubeMap>> m_cubeMaps;
	std::vector<std::shared_ptr<Mesh>> m_meshes;

	//void LoadResources(std::string _fileName){} add soon
	
	void AddShader(std::string _vertTXT, std::string _fragTXT, std::string _shaderName);
	void AddMaterial(std::weak_ptr<Shader> _baseShader, std::string _materialName);
	void AddTexture(std::string _filePath, std::string _textureName);
	void AddTexture(unsigned int _index, std::string _textureName);
	void AddCubeMap(std::string _filePathXPos, std::string _filePathXNeg, std::string _filePathYPos, std::string _filePathYNeg, std::string _filePathZPos, std::string _filePathZNeg, std::string _cubeMapName);
	void AddMesh(std::string _filePath, std::string _meshName, float _importScale);
};


#endif