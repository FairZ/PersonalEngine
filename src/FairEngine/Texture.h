#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Resource.h"
#include <GL/glew.h>

/// \brief Resource to handle the loading and storage of textures
class Texture : public Resource
{
public:
	/// \private
	Texture(std::string _filePath, std::string _textureName);
	/// \private
	Texture(GLuint _index, std::string _textureName);
	/// \private
	~Texture();

	GLuint GetTexIndex(){return m_texIndex;}
private:
	GLuint m_texIndex;
};

/// \brief Resource to handle the loading and storage of cubemaps
class CubeMap : public Resource
{
public:
	/// \private
	CubeMap(std::string _filePaths[6], std::string _cubeMapName);
	/// \private
	~CubeMap();

	GLuint GetTexIndex() { return m_texIndex; }
private:
	GLuint m_texIndex;
};

#endif