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
	Texture(GLuint _index, std::string _textureName);
	/// \private
	~Texture();

	GLuint GetTexIndex(){return m_texIndex;}
private:
	GLuint m_texIndex;
};

class CubeMap : public Resource
{
public:
	CubeMap(std::string _filePathXPos, std::string _filePathXNeg, std::string _filePathYPos, std::string _filePathYNeg, std::string _filePathZPos, std::string _filePathZNeg, std::string _cubeMapName);
	~CubeMap();

	GLuint GetTexIndex() { return m_texIndex; }
private:
	GLuint m_texIndex;
};

#endif