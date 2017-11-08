#include "TurnTable.h"
#include "Transform.h"
#include "Entity.h"

void TurnTable::Awake()
{
	m_transform = m_entity->m_transform;
}

void TurnTable::Update()
{
	//change to delta-time
	m_transform.lock()->Rotate(glm::vec3(0,0.01f,0));
}