#ifndef _MESH_H
#define _MESH_H
#include "Resource.h"
#include <GL/glew.h>

/// \brief Resource to handle the loading and storage of meshes
///
/// A single mesh can be accessed by multiple entities
class Mesh : public Resource
{
public:
	///\private
	Mesh(std::string _name, std::string _filePath, float _importScale);
	/// \private
	~Mesh();

	GLuint GetVAOIndex(){return m_VAOIndex;}
	unsigned int GetNumOfVertices(){return m_numOfVertices;}

private:
	void LoadOBJ(std::string _filePath, float _importScale);

	GLuint m_VAOIndex;
	unsigned int m_numOfVertices;
};


#endif