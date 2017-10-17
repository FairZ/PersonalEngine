#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <memory>
#include <vector>
#include <string>
#include "Component.h"

class Transform;
class Scene;

using namespace std;

class Entity
{
	friend class Engine;

public:
	Entity(string _name);
	shared_ptr<Transform> m_transform;

	string GetName();
	unsigned char GetLayer();
	void Destroy();

	template<typename T>
	weak_ptr<T> AddComponent()
	{
		static_assert(is_base_of<Component,T>::value,"Added class must be derived from component");
		shared_ptr<T> newComponent = make_shared<T>();
		m_components.push_back(newComponent);

		weak_ptr<T> retval = newComponent;
		return retval;
	}
	
	template<typename T>
	weak_ptr<T> GetComponent()
	{
		static_assert(is_base_of<Component,T>::value,"Searched for class must be derived from component");
		weak_ptr<T> retval;

		for(unsigned int i = 0; i < m_components.size();i++)
		{
			T* check = dynamic_cast<T*>(m_components.at(i).get());
	
			if (check != nullptr)
			{
				retval = m_components.at(i);
			}
		}
	
		return retval;
	}

	static weak_ptr<Entity> CreateEntity(string _name);
	static weak_ptr<Entity> FindEntity(string _name);



private:
	string m_name;
	unsigned char m_layer;
	vector<shared_ptr<Component>> m_components;
	static weak_ptr<Scene> m_scene;

	void Update();
	//void Render(); may not be neccessary depends on rendering engine 
	void Awake();

	//further functions can be added here
	//bool Load(params); for level loading

};



#endif