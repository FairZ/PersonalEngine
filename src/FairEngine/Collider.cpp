#include "Collider.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Entity.h"
#include "Scene.h"
#include "CollisionResolver.h"

void Collider::Start()
{
	//this function is intended to be overwritten but provides a guid for further colliders
	//the references must first be set and then the collider should register itself with the collision resolver
	m_transform = m_entity->m_transform;
	m_rigidBody = m_entity->GetComponent<RigidBody>();

	m_entity->GetScene().lock()->GetCollisionResolver().lock()->RegisterCollider(m_entity->GetComponent<Collider>());
}

void Collider::Destroy()
{
	m_transform.reset();
	m_rigidBody.reset();

	//if destroyed the collider should remove itself from the collision resolver
	m_entity->GetScene().lock()->GetCollisionResolver().lock()->RemoveCollider(this);
}

glm::vec3 Collider::GetMax()
{
	//get the maximum point using extents and center
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
	//get the minimum point using extents and center
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
