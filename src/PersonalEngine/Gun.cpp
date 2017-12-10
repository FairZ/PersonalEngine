#include "Gun.h"
#include "Bullet.h"
#include "Input.h"
#include <string>
#include "RigidBody.h"

void Gun::Update()
{
	if(Input::GetMouseButtonDown(0))
	{
		Shoot();
	}
}

void Gun::Start()
{
	m_ammoFired = 0;
	m_resetting = false;
	for(int i = 0; i < 30; i++)
	{
		std::weak_ptr<Bullet> bullet = Entity::InstantiatePrefab<Bullet>("Bullet",m_entity->GetName(), glm::vec3(0,0,5), glm::vec3(),glm::vec3(0.2f));
		m_ammoPool.push_back(bullet);
	}
	SetReferences();
}

void Gun::Shoot()
{
	if(m_ammoFired >= 30)
	{
		m_ammoFired = 0;
		m_resetting = true;
	}

	if (m_resetting)
		m_ammoPool[m_ammoFired].lock()->Reset();
	else
		m_ammoPool[m_ammoFired].lock()->SetActive(true);

	m_ammoPool[m_ammoFired].lock()->m_transform->DetachFromParent();

	m_ammoPool[m_ammoFired].lock()->GetComponent<RigidBody>().lock()->SetLinearVelocity(m_entity->m_transform->GetForward() * 25.0f);

	m_ammoFired++;

}

void Gun::SetReferences()
{
	m_transform = m_entity->m_transform;
}
