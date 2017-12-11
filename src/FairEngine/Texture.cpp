#include "Texture.h"
#include <SOIL/SOIL.h>

Texture::Texture(std::string _filePath, std::string _textureName)
{
	m_name = _textureName;
	//use SOIL to load in and set up a texture for the given image
	m_texIndex = SOIL_load_OGL_texture(_filePath.c_str(),
										SOIL_LOAD_AUTO,
										SOIL_CREATE_NEW_ID,
										SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS);
}

Texture::Texture(GLuint _index, std::string _textureName)
{
	m_texIndex = _index;
	m_name = _textureName;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texIndex);
}

CubeMap::CubeMap(std::string _filePaths[6], std::string _cubeMapName)
{
	m_name = _cubeMapName;
	//use SOIL to load in the textures to a cubemap
	m_texIndex = SOIL_load_OGL_cubemap(_filePaths[0].c_str(), 
										_filePaths[1].c_str(), 
										_filePaths[2].c_str(), 
										_filePaths[3].c_str(), 
										_filePaths[4].c_str(), 
										_filePaths[5].c_str(), 
										SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	//set texture parameters
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texIndex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

CubeMap::~CubeMap()
{
	glDeleteTextures(1, &m_texIndex);
}
