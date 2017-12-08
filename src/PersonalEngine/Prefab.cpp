#include "Prefab.h"
#include "Entity.h"
#include "Transform.h"


Prefab::Prefab(std::weak_ptr<Entity> _entity, std::string _prefabName)
{
	m_name = _prefabName;
	m_entity = std::make_shared<Entity>(*_entity.lock().get());
	m_entity->RealignComponents();
	m_entity->m_transform->DetachChildren();
	m_entity->m_transform->DetachFromParent();

}

Entity Prefab::GetEntity()
{
	return *m_entity.get();
}