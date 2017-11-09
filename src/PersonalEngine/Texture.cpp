#include "Texture.h"
#include <SOIL/SOIL.h>

Texture::Texture(std::string _filePath, std::string _textureName)
{
	m_name = _textureName;

	m_texIndex = SOIL_load_OGL_texture(_filePath.c_str(),
																		SOIL_LOAD_AUTO,
																		SOIL_CREATE_NEW_ID,
																		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texIndex);
}