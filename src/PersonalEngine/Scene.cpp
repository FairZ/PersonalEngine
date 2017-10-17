#include "Scene.h"

void Scene::AddEntity(std::shared_ptr<Entity> _entity)
{
	m_entities.push_back(_entity);
}