#include "BulletBehaviour.h"
#include "Time.h"
#include "Entity.h"

void BulletBehaviour::ResetTimeAlive()
{
	m_timeAlive = 0.0f;
}

void BulletBehaviour::Awake()
{
	m_timeAlive = 0.0f;
}

void BulletBehaviour::Update()
{
	m_timeAlive += Time::GetDeltaTimeSec();

	if (m_timeAlive > 20)
	{
		m_entity->SetActive(false);
	}
}