#include "Gun.h"
#include "Entity.h"
#include "Input.h"
#include "SphereCollider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"

void Gun::SetBullet(std::weak_ptr<Prefab> _prefab)
{
	m_bullet = _prefab;
}

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
	for(int i = 0; i < 30; i++)
	{
		std::weak_ptr<Entity> bullet = Entity::InstantiatePrefab(m_bullet, m_entity->GetName());
		bullet.lock()->SetActive(false);
		m_ammoPool.push_back(bullet);
	}
}

void Gun::Shoot()
{
	bool resetting = false;
	if(m_ammoFired >= 30)
	{
		m_ammoFired = 0;
		resetting = true;
	}

	if (resetting)
		m_ammoPool[m_ammoFired].lock()->ResetToPrefab();
	else
		m_ammoPool[m_ammoFired].lock()->SetActive(true);

	m_ammoFired++;

}