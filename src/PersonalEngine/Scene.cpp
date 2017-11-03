#include "Scene.h"
#include "Entity.h"

void Scene::AddEntity(std::shared_ptr<Entity> _entity)
{
	m_entities.push_back(_entity);
}

void Scene::AddResource(std::shared_ptr<Resource> _resource)
{
	m_resources.push_back(_resource);
}

void Scene::Update()
{
	for(auto i : m_entities)
	{
		i->Update();
	}
}

void Scene::Render()
{
	for(auto i : m_entities)
	{
		i->Render();
	}
}