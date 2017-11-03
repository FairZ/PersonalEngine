#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Resource.h"
#include <glm/glm.hpp>

class Texture : public Resource
{
public:
	static std::weak_ptr<Texture> LoadImage(std::string _filePath);
	GLint GetTexIndex();
private:
	GLint texIndex;
};

#endif