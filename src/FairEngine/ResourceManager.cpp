#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "Entity.h"
#include "Sound.h"

std::weak_ptr<Shader> ResourceManager::GetShader(std::string _shaderName)
{
	//Contains string comparisons, should only be done on initialisations
	std::weak_ptr<Shader> retVal;
	for(auto i : m_shaders)
	{
		if(i->GetName() == _shaderName)
		{
			retVal = i;
			break;
		}
	}
	return retVal;
}

std::weak_ptr<Material> ResourceManager::GetMaterial(std::string _materialName)
{
	//Contains string comparisons, should only be done on initialisations
	std::weak_ptr<Material> retVal;
	for(auto i : m_materials)
	{
		if(i->GetName() == _materialName)
		{
			retVal = i;
			break;
		}
	}
	return retVal;
}

std::weak_ptr<Texture> ResourceManager::GetTexture(std::string _textureName)
{
	//Contains string comparisons, should only be done on initialisations
	std::weak_ptr<Texture> retVal;
	for(auto i : m_textures)
	{
		if(i->GetName() == _textureName)
		{
			retVal = i;
			break;
		}
	}
	return retVal;
}

std::weak_ptr<CubeMap> ResourceManager::GetCubeMap(std::string _cubeMapName)
{
	//Contains string comparisons, should only be done on initialisations
	std::weak_ptr<CubeMap> retVal;
	for (auto i : m_cubeMaps)
	{
		if (i->GetName() == _cubeMapName)
		{
			retVal = i;
			break;
		}
	}
	return retVal;
}

std::weak_ptr<Mesh> ResourceManager::GetMesh(std::string _meshName)
{
	//Contains string comparisons, should only be done on initialisations
	std::weak_ptr<Mesh> retVal;
	for(auto i : m_meshes)
	{
		if(i->GetName() == _meshName)
		{
			retVal = i;
			break;
		}
	}
	return retVal;
}

std::weak_ptr<Sound> ResourceManager::GetSound(std::string _soundName)
{
	//Contains string comparisons, should only be done on initialisations
	std::weak_ptr<Sound> retVal;
	for(auto i : m_sounds)
	{
		if(i->GetName() == _soundName)
		{
			retVal = i;
			break;
		}
	}
	return retVal;
}

ResourceManager::ResourceManager()
{
	//always add the shadow shader and material
	AddShader("Shaders/ShadowVertex.txt","Shaders/ShadowFragment.txt","ShadowShader");
	AddMaterial(GetShader("ShadowShader"),"ShadowMat");
}

//creates and adds a shader to the shader list
void ResourceManager::AddShader(std::string _vertTXT, std::string _fragTXT, std::string _shaderName)
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(_shaderName,_vertTXT.c_str(),_fragTXT.c_str());
	m_shaders.push_back(shader);
}

//creates and adds a material to the material list
void ResourceManager::AddMaterial(std::weak_ptr<Shader> _baseShader, std::string _materialName)
{
	std::shared_ptr<Material> material = std::make_shared<Material>(_baseShader,_materialName);
	m_materials.push_back(material);
}

//creates and adds a texture to the texture list
void ResourceManager::AddTexture(std::string _filePath, std::string _textureName)
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(_filePath, _textureName);
	m_textures.push_back(texture);
}

//creates and adds a texture to the texture list
void ResourceManager::AddTexture(unsigned int _index, std::string _textureName)
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(_index, _textureName);
	m_textures.push_back(texture);
}

//creates and adds a cubeMap to the cubeMap list
void ResourceManager::AddCubeMap(std::string _filePaths[6], std::string _cubeMapName)
{
	std::shared_ptr<CubeMap> cubeMap = std::make_shared<CubeMap>(_filePaths, _cubeMapName);
	m_cubeMaps.push_back(cubeMap);
}

//creates and adds a mesh to the mesh list
void ResourceManager::AddMesh(std::string _filePath, std::string _meshName, float _importScale)
{
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(_meshName, _filePath, _importScale);
	m_meshes.push_back(mesh);
}

//creates and adds a sound to the sound list
void ResourceManager::AddSound(std::string _oggFilePath, std::string _soundName)
{
	std::shared_ptr<Sound> sound = std::make_shared<Sound>(_soundName, _oggFilePath);
	m_sounds.push_back(sound);
}