#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Scene.h"
#include <string>
#include "Transform.h"

/// \brief An entity is an object within the game's scene
///
/// Each entity contains a number of components (always including a transform component)
/// it is the components which give functionality to each entity, this removes the need for excessive
/// and convoluted inheritence
class Entity
{
	friend class Scene;

public:
	/// \private
	Entity(std::string _name);
	Entity(){}

	/// \brief Every entity has a readily accessible transform component
	std::shared_ptr<Transform> m_transform;

	std::string GetName();
	std::weak_ptr<Scene> GetScene();

	void Destroy();

	/// \return Weak pointer to the added component
	template<typename T>
	std::weak_ptr<T> AddComponent();
	
	template<typename T>
	std::weak_ptr<T> GetComponent();

	/// \brief Creates an entity with custom transform values and adds it to the scene graph
	static std::weak_ptr<Entity> CreateEntity(std::string _name, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);
	/// \brief Creates an entity with default transform values and adds it to the scene graph
	static std::weak_ptr<Entity> CreateEntity(std::string _name);
	/// \brief Creates an entity with default transform values, adds it to the scene graph and sets it as the child of the given parent
	static std::weak_ptr<Entity> CreateEntity(std::string _name, std::string _parentName);
	/// \brief Creates an entity with custom transform values, adds it to the scene graph and sets it as the child of the given parent
	static std::weak_ptr<Entity> CreateEntity(std::string _name, std::string _parentName, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);
	/// \brief Find an entity of the given name from the scene graph
	static std::weak_ptr<Entity> FindEntity(std::string _name);

	template<typename T>
	static std::weak_ptr<T> InstantiatePrefab(std::string _name);

	template<typename T>
	static std::weak_ptr<T> InstantiatePrefab(std::string _name, std::string _parentName);

	template<typename T>
	static std::weak_ptr<T> InstantiatePrefab(std::string _name, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);

	template<typename T>
	static std::weak_ptr<T> InstantiatePrefab(std::string _name, std::string _parentName, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);

	void SetActive(bool _active);

	virtual void Reset(){}

protected:
	std::string m_name;
	std::vector<std::shared_ptr<Component>> m_components;
	static std::weak_ptr<Scene> m_scene;
	bool m_destroyed;
	bool m_active;

	void WakeComponent(std::weak_ptr<Component> _component);

	void Update();
	void FixedUpdate();
	void Render(); 
	void ShadowRender();
	void Start();
	virtual void Initialise(){}

	//further functions can be added here
	//bool Load(params); for level loading

};

template<typename T>
std::weak_ptr<T> Entity::AddComponent()
{
	//static assert to insure that the user has not input the wrong type of class
	static_assert(std::is_base_of<Component, T>::value, "Added class must be derived from component");
	//create a new component of the given type and add it to the component list
	std::shared_ptr<T> newComponent = std::make_shared<T>();
	m_components.push_back(newComponent);
	//set the new component's entity and resource manager pointers
	newComponent->m_entity = this;
	newComponent->m_resourceManager = m_scene.lock()->GetResourceManager();
	//set to new so it's start function will be run next update
	newComponent->m_new = true;
	//create a weak pointer to the new component and return it
	std::weak_ptr<T> retVal = newComponent;
	//run the component's wake function
	WakeComponent(retVal);
	return retVal;
}

template<typename T>
std::weak_ptr<T> Entity::GetComponent()
{
	//static assert to insure that the user has not input the wrong type of class
	static_assert(std::is_base_of<Component, T>::value, "Searched for class must be derived from component");
	std::weak_ptr<T> retval;
	//go through the component list and compare type using the dynamic cast function
	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		T* check = dynamic_cast<T*>(m_components.at(i).get());
		//if the cast is valid assign a weak pointer of the correct type
		if (check != nullptr)
		{
			retval = std::dynamic_pointer_cast<T>(m_components.at(i));
			break;
		}
	}
	return retval;
}

template<typename T>
std::weak_ptr<T> Entity::InstantiatePrefab(std::string _name)
{
	static_assert(std::is_base_of<Entity, T>::value, "Prefab must be derived from of Entity");
	std::weak_ptr<T> retval;
	//controlled crash when no scene exists, will want to change to better error handling
	assert(!m_scene.expired());

	//create, initialise and add the new entity to the scene graph
	std::shared_ptr<T> newPrefab = std::make_shared<T>();
	m_scene.lock()->AddEntity(newPrefab);
	newPrefab->m_name = _name;
	newPrefab->m_transform = std::make_shared<Transform>();
	newPrefab->m_transform->m_entity = newPrefab.get();
	newPrefab->m_transform->m_position = glm::vec3();
	newPrefab->m_transform->m_rotation = glm::vec3();
	newPrefab->m_transform->m_scale = glm::vec3(1, 1, 1);
	newPrefab->Initialise();
	retval = newPrefab;

	return retval;
}

template<typename T>
std::weak_ptr<T> Entity::InstantiatePrefab(std::string _name, std::string _parentName)
{
	static_assert(std::is_base_of<Entity, T>::value, "Prefab must be derived from of Entity");
	std::weak_ptr<T> retval;
	//controlled crash when no scene exists, will want to change to better error handling
	assert(!m_scene.expired());

	//create, initialise and add the new entity to the scene graph
	std::shared_ptr<T> newPrefab = std::make_shared<T>();
	m_scene.lock()->AddEntity(newPrefab);
	newPrefab->m_name = _name;
	newPrefab->m_transform = std::make_shared<Transform>();
	newPrefab->m_transform->m_entity = newPrefab.get();
	FindEntity(_parentName).lock()->m_transform->AddChild(newEntity);
	newPrefab->m_transform->m_position = glm::vec3();
	newPrefab->m_transform->m_rotation = glm::vec3();
	newPrefab->m_transform->m_scale = glm::vec3(1, 1, 1);
	newPrefab->Initialise();
	retval = newPrefab;

	return retval;
}

template<typename T>
std::weak_ptr<T> Entity::InstantiatePrefab(std::string _name, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
{
	static_assert(std::is_base_of<Entity, T>::value, "Prefab must be derived from of Entity");
	std::weak_ptr<T> retval;
	//controlled crash when no scene exists, will want to change to better error handling
	assert(!m_scene.expired());

	//create, initialise and add the new entity to the scene graph
	std::shared_ptr<T> newPrefab = std::make_shared<T>();
	m_scene.lock()->AddEntity(newPrefab);
	newPrefab->m_name = _name;
	newPrefab->m_transform = std::make_shared<Transform>();
	newPrefab->m_transform->m_entity = newPrefab.get();
	newPrefab->m_transform->m_position = _position;
	newPrefab->m_transform->m_rotation = _rotation;
	newPrefab->m_transform->m_scale = _scale;
	newPrefab->Initialise();
	retval = newPrefab;

	return retval;
}

template<typename T>
std::weak_ptr<T> Entity::InstantiatePrefab(std::string _name, std::string _parentName, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
{
	static_assert(std::is_base_of<Entity, T>::value, "Prefab must be derived from of Entity");
	std::weak_ptr<T> retval;
	//controlled crash when no scene exists, will want to change to better error handling
	assert(!m_scene.expired());

	//create, initialise and add the new entity to the scene graph
	std::shared_ptr<T> newPrefab = std::make_shared<T>();
	m_scene.lock()->AddEntity(newPrefab);
	newPrefab->m_name = _name;
	newPrefab->m_transform = std::make_shared<Transform>();
	newPrefab->m_transform->m_entity = newPrefab.get();
	FindEntity(_parentName).lock()->m_transform->AddChild(newPrefab);
	newPrefab->m_transform->m_position = _position;
	newPrefab->m_transform->m_rotation = _rotation;
	newPrefab->m_transform->m_scale = _scale;
	newPrefab->Initialise();
	retval = newPrefab;

	return retval;
}
#endif