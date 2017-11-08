#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <memory>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Component.h"

class Transform;
class Scene;

class Entity
{
	friend class Scene;

public:
	Entity(std::string _name);
	std::shared_ptr<Transform> m_transform;

	std::string GetName();
	unsigned char GetLayer();
	void Destroy();

	template<typename T>
	std::weak_ptr<T> AddComponent()
	{
		static_assert(std::is_base_of<Component,T>::value,"Added class must be derived from component");
		std::shared_ptr<T> newComponent = std::make_shared<T>();
		m_components.push_back(newComponent);
		newComponent->m_entity = this;
		newComponent->m_resourceManager = m_scene.lock()->GetResourceManager();
		std::weak_ptr<T> retval = newComponent;
		return retval;
	}
	
	template<typename T>
	std::weak_ptr<T> GetComponent()
	{
		static_assert(std::is_base_of<Component,T>::value,"Searched for class must be derived from component");
		std::weak_ptr<T> retval;

		for(unsigned int i = 0; i < m_components.size();i++)
		{
			T* check = dynamic_cast<T*>(m_components.at(i).get());
	
			if (check != nullptr)
			{
				retval = std::dynamic_pointer_cast<T>(m_components.at(i));
				break;
			}
		}
	
		return retval;
	}

	static std::weak_ptr<Entity> CreateEntity(std::string _name, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);
	static std::weak_ptr<Entity> CreateEntity(std::string _name);
	static std::weak_ptr<Entity> FindEntity(std::string _name);



private:
	std::string m_name;
	unsigned char m_layer;
	std::vector<std::shared_ptr<Component>> m_components;
	static std::weak_ptr<Scene> m_scene;

	void Update();
	void Render(); 
	void Awake();

	//further functions can be added here
	//bool Load(params); for level loading

};



#endif