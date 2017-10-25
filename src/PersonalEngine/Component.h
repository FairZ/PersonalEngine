#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <memory>

class Component
{
	friend class Entity;

public:


protected:
	Entity* m_entity;

	virtual void Update(){}
	virtual void Awake(){}
	virtual void Render(){}
	virtual void Destroy(){}
};


#endif