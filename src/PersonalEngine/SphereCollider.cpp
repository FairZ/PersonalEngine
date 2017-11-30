#include "SphereCollider.h"
#include "Entity.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Scene.h"
#include "CollisionResolver.h"

void SphereCollider::SetRadius(float _radius)
{
	m_radius = _radius;
	m_extents = glm::vec3(_radius);
}

void SphereCollider::Awake()
{
	m_transform = m_entity->m_transform;
	m_rigidBody = m_entity->GetComponent<RigidBody>();
	m_type = 's';
	//ADD REGISTER OF COLLIDER
	m_entity->GetScene().lock()->GetCollisionResolver().lock()->RegisterCollider(m_entity->GetComponent<SphereCollider>());
	SetRadius(1.0f);
}