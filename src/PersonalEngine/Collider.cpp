#include "Collider.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Entity.h"
#include "Scene.h"
#include "CollisionResolver.h"

void Collider::Awake()
{
	m_transform = m_entity->m_transform;
	m_rigidBody = m_entity->GetComponent<RigidBody>();

	m_entity->GetScene().lock()->GetCollisionResolver().lock()->RegisterCollider(m_entity->GetComponent<Collider>());
}


void Collider::Destroy()
{
	m_transform.reset();
	m_rigidBody.reset();

	m_entity->GetScene().lock()->GetCollisionResolver().lock()->RemoveCollider(m_entity->GetComponent<Collider>());
}

glm::vec3 Collider::GetMax()
{
	glm::vec3 transformedCenter = m_transform.lock()->GetTransformationMatrix() * glm::vec4(m_center,1);
	return transformedCenter + (m_extents * m_transform.lock()->GetScale());
}

glm::vec3 Collider::GetExtents()
{
	return m_extents;
}

void Collider::SetCenter(glm::vec3 _center)
{
	m_center = _center;
}

glm::vec3 Collider::GetMin()
{
	glm::vec3 transformedCenter = m_transform.lock()->GetTransformationMatrix() * glm::vec4(m_center, 1);
	return transformedCenter - (m_extents * m_transform.lock()->GetScale());
}

char Collider::GetType()
{
	return m_type;
}

glm::vec3 Collider::GetWorldSpaceCenter()
{
	return m_transform.lock()->GetTransformationMatrix() * glm::vec4(m_center, 1);
}

std::weak_ptr<RigidBody> Collider::GetRigidBody()
{
	return m_rigidBody;
}
