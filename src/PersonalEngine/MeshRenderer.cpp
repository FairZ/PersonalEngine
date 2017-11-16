#include "MeshRenderer.h"
#include "Material.h"
#include "Mesh.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Transform.h"

void MeshRenderer::SetMesh(std::string _meshName)
{
	m_mesh = m_resourceManager.lock()->GetMesh(_meshName);
}

void MeshRenderer::SetMaterial(std::string _materialName)
{
	m_material = m_resourceManager.lock()->GetMaterial(_materialName);
}

std::weak_ptr<Material> MeshRenderer::GetMaterial()
{
	return m_material;
}

void MeshRenderer::Awake()
{
	//initialise the string to avoid a string being generated every frame when passing in the model matrix
	modelMat = "modelMat";
}

void MeshRenderer::Render()
{
	//pass the model matrix to the material
	m_material.lock()->SetMat4(modelMat, m_entity->m_transform->GetTransformationMatrix());

	//pass all set uniforms into the shader
	m_material.lock()->ReadyForDraw();

	//bind VAO and enable attributes
	glBindVertexArray(m_mesh.lock()->GetVAOIndex());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	
	//draw the mesh
	glDrawArrays(GL_TRIANGLES, 0, m_mesh.lock()->GetNumOfVertices());

	//unbind VAO and disable attributes
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glBindVertexArray(0);
}