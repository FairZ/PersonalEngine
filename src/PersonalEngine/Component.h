#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class Component
{
	friend class Entity;

public:


protected:
	virtual void Update(){}
	virtual void Awake(){}
	virtual void Destroy(){}
};


#endif