#ifndef _PREFAB_H_
#define _PREFAB_H_
#include "Resource.h"
#include <memory>

class Entity;

class Prefab : public Resource
{
public:
	Prefab(std::weak_ptr<Entity> _entity, std::string _prefabName);
	Entity GetEntity();
private:
	std::shared_ptr<Entity> m_entity;
};


#endif