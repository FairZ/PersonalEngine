#ifndef _GUN_H_
#define _GUN_H_
#include "Component.h"
#include <vector>

class Bullet;
class Transform;

class Gun : public Component
{
public:

private:
	void Update();
	void Start();
	void Shoot();
	void SetReferences();

	bool m_resetting;

	unsigned int m_ammoFired;

	std::weak_ptr<Transform> m_transform;

	std::vector<std::weak_ptr<Bullet>> m_ammoPool;
};

#endif