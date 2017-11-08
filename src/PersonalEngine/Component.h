#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <memory>

class ResourceManager;

class Component
{
	friend class Entity;

public:


protected:
	Entity* m_entity;

	std::weak_ptr<ResourceManager> m_resourceManager;

	virtual void Update(){}
	virtual void Awake(){}
	virtual void Render(){}
	virtual void Destroy(){}
};


#endif