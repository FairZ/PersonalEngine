#include "Mesh.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Mesh::Mesh(std::string _name, std::string _filePath, float _importScale)
{
	m_name = _name;
	LoadMesh(_filePath, _importScale);
}

Mesh::~Mesh()
{
	//delete all VAOs
	for (unsigned int i = 0; i < m_VAOs.size(); i++)
	{
		glDeleteVertexArrays(1, &m_VAOs.at(i));
	}
}

GLuint Mesh::GetVAOIndex(unsigned int _index)
{
	GLuint RetVal = 0;

	if (_index >= 0 && _index < m_indexNumbers.size())
	{
		RetVal = m_VAOs.at(_index);
	}

	return RetVal;
}

unsigned int Mesh::GetNumOfIndices(unsigned int _index)
{
	//return the number of indices in a given VAO
	unsigned int RetVal;

	if (_index >= 0 && _index < m_indexNumbers.size())
	{
		RetVal = m_indexNumbers.at(_index);
	}

	return RetVal;
}

void Mesh::LoadMesh(std::string _fileName, float _importScale)
{
	//uses Assimp to import a large variety of model files
	Assimp::Importer importer;
	//generate tangent space data for normal mapping, triangulate any quad meshes, and flip the UVs due to OpenGL's upside down texture coordinate system
	const aiScene* scene = importer.ReadFile(_fileName, aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_Triangulate  | aiProcess_FlipUVs);

	//for every object in the loaded file
	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[i];

		std::vector<glm::vec2> rawUVData;
		std::vector<glm::vec3> rawPositionData;
		std::vector<glm::vec3> rawNormalData;
		std::vector<glm::vec3> rawTangentData;
		std::vector<glm::vec3> rawBitangentData;
		std::vector<unsigned int> indices;

		//assign the data into temporary storage vectors
		for (unsigned int j = 0; j < mesh->mNumVertices; j++)
		{
			rawPositionData.push_back(glm::vec3(mesh->mVertices[j].x * _importScale, mesh->mVertices[j].y * _importScale, mesh->mVertices[j].z * _importScale));
			rawUVData.push_back(glm::vec2(mesh->mTextureCoords[0][j].x,mesh->mTextureCoords[0][j].y));
			rawNormalData.push_back(glm::vec3(mesh->mNormals[j].x,mesh->mNormals[j].y, mesh->mNormals[j].z));
			rawTangentData.push_back(glm::vec3(mesh->mTangents[j].x,mesh->mTangents[j].y, mesh->mTangents[j].z));
			rawBitangentData.push_back(glm::vec3(mesh->mBitangents[j].x,mesh->mBitangents[j].y, mesh->mBitangents[j].z));
		}
		for(unsigned int f = 0; f < mesh->mNumFaces; f++)
		{
			aiFace face = mesh->mFaces[f];
			for(unsigned int ind = 0; ind < face.mNumIndices; ind++)
			{
				indices.push_back(face.mIndices[ind]);
			}
		}

		//generate VAO and push the data to OpenGl
		m_VAOs.push_back(GLuint());
		glGenVertexArrays(1, &m_VAOs.at(i));
		glBindVertexArray(m_VAOs.at(i));

		GLuint posBuffer = 0;
		glGenBuffers(1, &posBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rawPositionData.size(), &rawPositionData[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
		
		GLuint normBuffer = 0;
		glGenBuffers(1, &normBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rawNormalData.size(), &rawNormalData[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
		
		GLuint texBuffer = 0;
		glGenBuffers(1, &texBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * rawUVData.size(), &rawUVData[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0 );		

		GLuint tangentBuffer = 0;
		glGenBuffers(1,&tangentBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rawTangentData.size(), &rawTangentData[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,0,0);		

		GLuint bitangentBuffer = 0;
		glGenBuffers(1, &bitangentBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rawBitangentData.size(), &rawBitangentData[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);		

		m_indexNumbers.push_back(indices.size());
		GLuint EBO;
		glGenBuffers(1,&EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		glBindVertexArray( 0 );
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);

		glDeleteBuffers(1, &posBuffer);
		glDeleteBuffers(1, &normBuffer);
		glDeleteBuffers(1, &texBuffer);
		glDeleteBuffers(1, &tangentBuffer);
		glDeleteBuffers(1, &bitangentBuffer);
		glDeleteBuffers(1, &EBO);

	}
}