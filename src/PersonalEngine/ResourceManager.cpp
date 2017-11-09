#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

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

void ResourceManager::AddShader(std::string _vertTXT, std::string _fragTXT, std::string _shaderName)
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(_shaderName,_vertTXT.c_str(),_fragTXT.c_str());
	m_shaders.push_back(shader);
}

void ResourceManager::AddMaterial(std::weak_ptr<Shader> _baseShader, std::string _materialName)
{
	std::shared_ptr<Material> material = std::make_shared<Material>(_baseShader,_materialName);
	m_materials.push_back(material);
}

void ResourceManager::AddTexture(std::string _filePath, std::string _textureName)
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(_filePath, _textureName);
	m_textures.push_back(texture);
}

void ResourceManager::AddMesh(std::string _filePath, std::string _meshName)
{
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(_meshName, _filePath);
	m_meshes.push_back(mesh);
}