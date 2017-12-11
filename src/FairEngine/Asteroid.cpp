#include "Asteroid.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "SphereCollider.h"

void Asteroid::Initialise()
{
	m_active = true;
	//setup initial positions for later reset
	m_initialPosition = m_transform->GetLocalPosition();
	m_initialRotation = m_transform->GetLocalRotation();
	m_initialScale = m_transform->GetLocalScale();
	std::weak_ptr<MeshRenderer> meshRenderer = AddComponent<MeshRenderer>();
	meshRenderer.lock()->SetMesh("MeteorMesh");
	meshRenderer.lock()->SetMaterial(0, "Asteroid");
	std::weak_ptr<SphereCollider> sphere = AddComponent<SphereCollider>();
	sphere.lock()->SetRadius(9.0f);
}

void Asteroid::Reset()
{
	//return to initial values
	m_transform->SetLocalPosition(m_initialPosition);
	m_transform->SetLocalRotation(m_initialRotation);
	m_transform->SetLocalScale(m_initialScale);
	std::weak_ptr<MeshRenderer> meshRenderer = GetComponent<MeshRenderer>();
	meshRenderer.lock()->SetMesh("MeteorMesh");
	meshRenderer.lock()->SetMaterial(0, "Asteroid");
}