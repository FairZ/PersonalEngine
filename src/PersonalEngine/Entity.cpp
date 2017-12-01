#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "Engine.h"
#include "ExceptionHandler.h"

//static variable initialization
std::weak_ptr<Scene> Entity::m_scene = Engine::m_currentScene;

std::string Entity::GetName()
{
	return m_name;
}

std::weak_ptr<Scene> Entity::GetScene()
{
	return m_scene;
}

std::weak_ptr<Entity> Entity::CreateEntity(std::string _name, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
{
	std::weak_ptr<Entity> retval;

	//ensures that the static reference to the current scene is up to date when creating a new entity
	m_scene = Engine::m_currentScene;

	//controlled crash when no scene exists, will want to change to better error handling
	assert(!m_scene.expired());

	//create, initialise and add the new entity to the scene graph
	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(_name);
	m_scene.lock()->AddEntity(newEntity);
	newEntity->m_transform = std::make_shared<Transform>();
	newEntity->m_transform->m_position = _position;
	newEntity->m_transform->m_rotation = _rotation;
	newEntity->m_transform->m_scale = _scale;
	newEntity->m_transform->m_entity = newEntity.get();
	retval = newEntity;

	return retval;
}

std::weak_ptr<Entity> Entity::CreateEntity(std::string _name)
{
	std::weak_ptr<Entity> retval;
	//ensures that the static reference to the current scene is up to date when creating a new entity
	m_scene = Engine::m_currentScene;
	//controlled crash when no scene exists, will want to change to better error handling
	assert(!m_scene.expired());

	//create, initialise and add the new entity to the scene graph
	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(_name);
	m_scene.lock()->AddEntity(newEntity);
	newEntity->m_transform = std::make_shared<Transform>();
	newEntity->m_transform->m_position = glm::vec3();
	newEntity->m_transform->m_rotation = glm::vec3();
	newEntity->m_transform->m_scale = glm::vec3(1,1,1);
	newEntity->m_transform->m_entity = newEntity.get();
	retval = newEntity;

	return retval;
}

std::weak_ptr<Entity> Entity::CreateEntity(std::string _name, std::string _parentName)
{
	std::weak_ptr<Entity> retval;
	//ensures that the static reference to the current scene is up to date when creating a new entity
	m_scene = Engine::m_currentScene;
	//controlled crash when no scene exists, will want to change to better error handling
	assert(!m_scene.expired());

	//create, initialise, add the new entity to the scene graph and to the parent
	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(_name);
	m_scene.lock()->AddEntity(newEntity);
	newEntity->m_transform = std::make_shared<Transform>();
	FindEntity(_parentName).lock()->m_transform->AddChild(newEntity);
	newEntity->m_transform->m_position = glm::vec3();
	newEntity->m_transform->m_rotation = glm::vec3();
	newEntity->m_transform->m_scale = glm::vec3(1,1,1);
	newEntity->m_transform->m_entity = newEntity.get();
	retval = newEntity;

	return retval;
}

std::weak_ptr<Entity> Entity::CreateEntity(std::string _name, std::string _parentName, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
{
	std::weak_ptr<Entity> retval;

	//ensures that the static reference to the current scene is up to date when creating a new entity
	m_scene = Engine::m_currentScene;

	//controlled crash when no scene exists, will want to change to better error handling
	assert(!m_scene.expired());

	//create, initialise, add the new entity to the scene graph and to the parent
	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(_name);
	m_scene.lock()->AddEntity(newEntity);
	newEntity->m_transform = std::make_shared<Transform>();
	FindEntity(_parentName).lock()->m_transform->AddChild(newEntity);
	newEntity->m_transform->m_position = _position;
	newEntity->m_transform->m_rotation = _rotation;
	newEntity->m_transform->m_scale = _scale;
	newEntity->m_transform->m_entity = newEntity.get();
	retval = newEntity;

	return retval;
}

std::weak_ptr<Entity> Entity::FindEntity(std::string _name)
{
	//contains string comparisons, should only be run at intialisations
	weak_ptr<Entity> retval;

	//run through the scene graph and check for an entity of the given name
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
	m_destroyed = false;
}

void Entity::WakeComponent(std::weak_ptr<Component> _component)
{
	for (auto i : m_components)
	{
		if (i.get() == _component.lock().get())
		{
			i->Awake();
		}
	}
}

void Entity::Update()
{
	//go through every component and update it
	for (auto i : m_components)
	{
		if (i->m_new)
		{
			i->Start();
			i->m_new = false;
		}
		i->Update();
	}
}

void Entity::FixedUpdate()
{
	//go through every component and update it
	for (auto i : m_components)
	{
		if (i->m_new)
		{
			i->Start();
			i->m_new = false;
		}
		i->FixedUpdate();
	}
}

void Entity::Render()
{
	//go through every component and Awake it
	for (auto i : m_components)
	{
		i->Render();
	}
}

void Entity::Start()
{
	//go through every component and Awake it
	for (auto i : m_components)
	{
		i->Start();
		i->m_new = false;
	}
	m_transform->Start();
	m_transform->m_new = false;
}

void Entity::Destroy()
{
	//go through every component and Destroy it
	for (auto i : m_components)
	{
		i->Destroy();
	}
	//delete the components from memory
	m_components.clear();
	//destroy the transform component and recursively delete children
	m_transform->Destroy();
	//delete the transform component from memory
	m_transform.reset();
	//flag the entity for removal from the scene graph
	m_destroyed = true;
}