#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <memory>

class ResourceManager;

/// \brief Abstract base class for components
///
/// Contains a few virtual functions and pointers to the entity that owns the component
/// and the current resource manager
class Component
{
	friend class Entity;

public:


protected:
	//while this is a raw pointer it is safe as there will never be a component without an entity
	//and when an entity gets destroyed it also deletes all components that it contains
	Entity* m_entity;

	std::weak_ptr<ResourceManager> m_resourceManager;

	virtual void Update(){}
	virtual void Awake(){}
	virtual void Render(){}
	virtual void Destroy(){}
};


#endif