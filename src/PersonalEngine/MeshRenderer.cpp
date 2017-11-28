#include "MeshRenderer.h"
#include "Material.h"
#include "Mesh.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Transform.h"

void MeshRenderer::SetMesh(std::string _meshName)
{
	m_model = m_resourceManager.lock()->GetMesh(_meshName);
	m_materials.resize(m_model.lock()->GetNumOfVAOs());
}

void MeshRenderer::SetMaterial(unsigned int _index, std::string _materialName)
{
	m_materials.at(_index) = m_resourceManager.lock()->GetMaterial(_materialName);
}

std::weak_ptr<Material> MeshRenderer::GetMaterial(unsigned int _index)
{
	return m_materials.at(_index);
}

void MeshRenderer::Awake()
{
	//initialise the string to avoid a string being generated every frame when passing in the model matrix
	modelMat = "modelMat";
}

void MeshRenderer::Render()
{
	//for every mesh in the model
	for(int i = 0; i < m_model.lock()->GetNumOfVAOs(); i++)
	{
		//pass the model matrix to the material
		m_materials.at(i).lock()->SetMat4(modelMat, m_entity->m_transform->GetTransformationMatrix());

		//pass all set uniforms into the shader
		m_materials.at(i).lock()->ReadyForDraw();

		//bind VAO and enable attributes
		glBindVertexArray(m_model.lock()->GetVAOIndex(i));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
	
		//draw the mesh
		glDrawElements(GL_TRIANGLES, m_model.lock()->GetNumOfIndices(i), GL_UNSIGNED_INT, 0);

		//unbind VAO and disable attributes
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
		glBindVertexArray(0);
	}
}