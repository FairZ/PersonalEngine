#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Resource.h"
#include <GL/glew.h>

class Texture : public Resource
{
public:
	Texture(std::string _filePath, std::string _textureName);
	~Texture();

	GLuint GetTexIndex(){return m_texIndex;}
private:
	GLuint m_texIndex;
};

#endif