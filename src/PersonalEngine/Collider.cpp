#include "Collider.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Entity.h"

void Collider::Awake()
{
	m_transform = m_entity->m_transform;
	m_rigidBody = m_entity->GetComponent<RigidBody>();

	//ADD REGISTER OF COLLIDER
	m_entity->GetScene();
}


void Collider::Destroy()
{
	m_transform.reset();
	m_rigidBody.reset();

	//ADD UNREGISTER OF COLLIDER
	m_entity->GetScene();
}

glm::vec3 Collider::GetMax()
{
	glm::vec3 transformedCenter = glm::vec4(m_center,1) * m_transform.lock()->GetTransformationMatrix();
	return transformedCenter + (m_extents * m_transform.lock()->GetScale());
}

glm::vec3 Collider::GetMin()
{
	glm::vec3 transformedCenter = glm::vec4(m_center,1) * m_transform.lock()->GetTransformationMatrix();
	return transformedCenter - (m_extents * m_transform.lock()->GetScale());
}