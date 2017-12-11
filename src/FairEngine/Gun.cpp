#include "Gun.h"
#include "Bullet.h"
#include "Input.h"
#include <string>
#include "RigidBody.h"
#include "AudioSource.h"

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
	//instantiate a number of bullet objects for the pool
	for(int i = 0; i < 30; i++)
	{
		std::weak_ptr<Bullet> bullet = Entity::InstantiatePrefab<Bullet>("Bullet",m_entity->GetName(), glm::vec3(0,0,5), glm::vec3(),glm::vec3(0.2f));
		m_ammoPool.push_back(bullet);
	}
	SetReferences();
}

void Gun::Shoot()
{
	//if all of the pool has been fired begin resetting them
	if(m_ammoFired >= 30)
	{
		m_ammoFired = 0;
		m_resetting = true;
	}

	//reset or activate the next bullet in the pool
	if (m_resetting)
		m_ammoPool[m_ammoFired].lock()->Reset();
	else
		m_ammoPool[m_ammoFired].lock()->SetActive(true);

	//detach it from this entity so that it can move freely
	m_ammoPool[m_ammoFired].lock()->m_transform->DetachFromParent();
	//fire it off with an initial velocity
	m_ammoPool[m_ammoFired].lock()->GetComponent<RigidBody>().lock()->SetLinearVelocity(m_entity->m_transform->GetForward() * 25.0f);

	//play a firing sound
	m_audio.lock()->Play();
	//increment the counter
	m_ammoFired++;

}

void Gun::SetReferences()
{
	m_transform = m_entity->m_transform;
	m_audio = m_entity->GetComponent<AudioSource>();
}
