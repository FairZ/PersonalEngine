#ifndef _GUN_H_
#define _GUN_H_
#include "Component.h"
#include <vector>

class Entity;
class Prefab;

class Gun : public Component
{
public:
	void SetBullet(std::weak_ptr<Prefab> _prefab);
private:
	void Update();
	void Start();
	void Shoot();

	std::weak_ptr<Prefab> m_bullet;

	unsigned int m_ammoFired;

	std::vector<std::weak_ptr<Entity>> m_ammoPool;
};

#endif