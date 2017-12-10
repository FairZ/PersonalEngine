#include "Bullet.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "FlyingController.h"
#include "BulletBehaviour.h"

void Bullet::Initialise()
{
	m_active = false;
	m_initialParent = m_transform->GetParent();
	m_initialPosition = m_transform->GetLocalPosition();
	m_initialRotation = m_transform->GetLocalRotation();
	m_initialScale = m_transform->GetLocalScale();
	std::weak_ptr<RigidBody> rb = AddComponent<RigidBody>();
	rb.lock()->SetDrag(1.0f);
	rb.lock()->SetGravity(glm::vec3());
	AddComponent<SphereCollider>();
	std::weak_ptr<MeshRenderer> meshRenderer = AddComponent<MeshRenderer>();
	meshRenderer.lock()->SetMesh("Ship");
	meshRenderer.lock()->SetMaterial(0, "SpaceShip");
	AddComponent<BulletBehaviour>();
}

void Bullet::Reset()
{
	m_active = true;
	if (!m_initialParent.expired())
		m_transform->AddParent(m_initialParent);
	m_transform->SetLocalPosition(m_initialPosition);
	m_transform->SetLocalRotation(m_initialRotation);
	m_transform->SetLocalScale(m_initialScale);
	std::weak_ptr<RigidBody> rb = GetComponent<RigidBody>();
	rb.lock()->SetLinearAcceleration(glm::vec3());
	rb.lock()->SetLinearVelocity(glm::vec3());
	rb.lock()->SetDrag(1.0f);
	rb.lock()->SetGravity(glm::vec3());
	std::weak_ptr<MeshRenderer> meshRenderer = GetComponent<MeshRenderer>();
	meshRenderer.lock()->SetMesh("Ship");
	meshRenderer.lock()->SetMaterial(0, "SpaceShip");
	GetComponent<BulletBehaviour>().lock()->ResetTimeAlive();
}
