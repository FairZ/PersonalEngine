#include "Bullet.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Transform.h"
#include "FlyingController.h"

void Bullet::Initialise()
{
	m_active = false;
	m_initialParent = m_transform->GetParent();
	m_initialPosition = m_transform->GetLocalPosition();
	m_initialRotation = m_transform->GetLocalRotation();
	m_initialScale = m_transform->GetLocalScale();
	AddComponent<FlyingController>();
	std::weak_ptr<MeshRenderer> meshRenderer = AddComponent<MeshRenderer>();
	meshRenderer.lock()->SetMesh("Ship");
	meshRenderer.lock()->SetMaterial(0, "SpaceShip");
}

void Bullet::Reset()
{
	if (!m_initialParent.expired())
		m_transform->AddParent(m_initialParent);
	m_transform->SetLocalPosition(m_initialPosition);
	m_transform->SetLocalRotation(m_initialRotation);
	m_transform->SetLocalScale(m_initialScale);
	std::weak_ptr<MeshRenderer> meshRenderer = GetComponent<MeshRenderer>();
	meshRenderer.lock()->SetMesh("Ship");
	meshRenderer.lock()->SetMaterial(0, "SpaceShip");
}
