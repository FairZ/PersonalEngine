#ifndef _MESH_H
#define _MESH_H
#include "Resource.h"
#include <GL/glew.h>


class Mesh : public Resource
{
public:
	Mesh(std::string _name, std::string _filePath);
	~Mesh();

	GLuint GetVAOIndex(){return m_VAOIndex;}
	unsigned int GetNumOfVertices(){return m_numOfVertices;}

private:
	void LoadOBJ(std::string _filePath);

	GLuint m_VAOIndex;
	unsigned int m_numOfVertices;
};


#endif