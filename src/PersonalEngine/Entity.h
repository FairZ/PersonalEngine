#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <memory>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Component.h"

class Transform;
class Scene;

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

	/// \brief Every entity has a readily accessible transform component
	std::shared_ptr<Transform> m_transform;

	std::string GetName();
	std::weak_ptr<Scene> GetScene();

	void Destroy();

	/// \return Weak pointer to the added component
	template<typename T>
	std::weak_ptr<T> AddComponent()
	{
		//static assert to insure that the user has not input the wrong type of class
		static_assert(std::is_base_of<Component,T>::value,"Added class must be derived from component");
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
	std::weak_ptr<T> GetComponent()
	{
		//static assert to insure that the user has not input the wrong type of class
		static_assert(std::is_base_of<Component,T>::value,"Searched for class must be derived from component");
		std::weak_ptr<T> retval;
		//go through the component list and compare type using the dynamic cast function
		for(unsigned int i = 0; i < m_components.size();i++)
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



private:
	std::string m_name;
	std::vector<std::shared_ptr<Component>> m_components;
	static std::weak_ptr<Scene> m_scene;
	bool m_destroyed;

	void WakeComponent(std::weak_ptr<Component> _component);

	void Update();
	void FixedUpdate();
	void Render(); 
	void Start();

	//further functions can be added here
	//bool Load(params); for level loading

};



#endif