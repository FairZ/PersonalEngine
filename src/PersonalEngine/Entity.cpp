#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "Engine.h"
#include "ExceptionHandler.h"

std::weak_ptr<Scene> Entity::m_scene = Engine::m_currentScene;

std::string Entity::GetName()
{
	return m_name;
}

unsigned char Entity::GetLayer()
{
	return m_layer;
}

std::weak_ptr<Entity> Entity::CreateEntity(std::string _name, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
{
	std::weak_ptr<Entity> retval;

	m_scene = Engine::m_currentScene;
	assert(!m_scene.expired());

	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(_name); //parameters should go into constructor
	m_scene.lock()->AddEntity(newEntity);
	newEntity->m_transform = std::make_shared<Transform>();
	newEntity->m_transform->m_position = _position;
	newEntity->m_transform->m_rotation = _rotation;
	newEntity->m_transform->m_scale = _scale;
	retval = newEntity;

	return retval;
}

std::weak_ptr<Entity> Entity::CreateEntity(std::string _name)
{
	std::weak_ptr<Entity> retval;

	m_scene = Engine::m_currentScene;
	assert(!m_scene.expired());

	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(_name); //parameters should go into constructor
	m_scene.lock()->AddEntity(newEntity);
	newEntity->m_transform = std::make_shared<Transform>();
	newEntity->m_transform->m_position = glm::vec3();
	newEntity->m_transform->m_rotation = glm::vec3();
	newEntity->m_transform->m_scale = glm::vec3(1,1,1);
	retval = newEntity;

	return retval;
}

std::weak_ptr<Entity> Entity::FindEntity(std::string _name)
{
	weak_ptr<Entity> retval;

	for(auto i : m_scene.lock()->m_entities)
	{
		if (i->m_name == _name)
		{
			retval = i;
			break;
		}
	}

	return retval;
}

Entity::Entity(std::string _name)
{
	m_name = _name;
}

void Entity::Update()
{
	//go through every component and update it
	for (auto i : m_components)
	{
		i->Update();
	}
	//run recursive Update function for children of current entity
}

void Entity::Render()
{
	//go through every component and Awake it
	for (auto i : m_components)
	{
		i->Render();
	}
	//run recursive Awake function for children of current entity
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