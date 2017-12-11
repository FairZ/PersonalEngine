#ifndef _MESH_H
#define _MESH_H
#include "Resource.h"
#include <vector>
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

	GLuint GetVAOIndex(unsigned int _index);
	unsigned int GetNumOfIndices(unsigned int _index);

	int GetNumOfVAOs(){return m_VAOs.size();}
private:
	void LoadMesh(std::string _filePath, float _importScale);

	std::vector<GLuint> m_VAOs;
	std::vector<unsigned int> m_indexNumbers;
};


#endif