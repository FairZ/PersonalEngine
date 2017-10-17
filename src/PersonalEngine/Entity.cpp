#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "Engine.h"
#include "ExceptionHandler.h"

weak_ptr<Scene> Entity::m_scene = Engine::m_currentScene;

std::string Entity::GetName()
{
	return m_name;
}

unsigned char Entity::GetLayer()
{
	return m_layer;
}

std::weak_ptr<Entity> Entity::CreateEntity()
{
	weak_ptr<Entity> retval;

	m_scene = Engine::m_currentScene;
	assert(!m_scene.expired());

	shared_ptr<Entity> newEntity = std::make_shared<Entity>(); //parameters should go into constructor
	m_scene.lock()->AddEntity(newEntity);
	retval = newEntity;

	return retval;
}

/*
std::weak_ptr<Entity> Entity::FindEntity(std::string _name)
{
	m_scene.lock();
}*/

void Entity::Update()
{
	//go through every component and update it
	for (auto i : m_components)
	{
		i->Update();
	}
	//run recursive Update function for children of current entity
	m_transform->Update();
}

void Entity::Awake()
{
	//go through every component and Awake it
	for (auto i : m_components)
	{
		i->Awake();
	}
	//run recursive Awake function for children of current entity
	m_transform->Awake();
}

void Entity::Destroy()
{
	//go through every component and Destroy it
	for (auto i : m_components)
	{
		i->Destroy();
		//delete the component
		i.reset();
	}
	//run recursive Destroy function for children of current entity
	m_transform->Destroy();
	//delete the transform component
	m_transform.reset();
}